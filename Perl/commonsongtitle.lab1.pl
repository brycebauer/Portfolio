######################################### 	
#    CSCI 305 - Programming Lab #1		
#										
#  < Bryce Bauer >			
#  < brycewbauer@gmail.com >			
#										
#########################################

# use strict;
# use warnings;
 use Encode;
 use utf8;
use Data::Dumper;

my $name = " Bryce Bauer";
my $partner = "Tabetha Boushey";
print "CSCI 305 Lab 1 submitted by $name and $partner.\n\n";

# Checks for the argument, fail if not given
if($#ARGV != 0) {
    
	print STDERR "You must specify the file name as the argument.\n";
    exit 4;
}

# Opens the file and assign it to handle INFILE
open(INFILE, $ARGV[0]) or die "Cannot open $ARGV[0]: $!.\n";

my $title = 0;
my $counter = 0;
my %biGram = ();

# This loops through each line of the file
while($line = <INFILE>) {
	
	# It returns the actual version of the text
	$title = decode_utf8($title);
	
	# Everything before the last <SEP> is now blank
	$title =~ s/.*\<SEP\>//;
	
	# All the symbols are taken out
	$title =~ s/([({\\_\-:\/"'+=*]|feat.).*$//g;
	
	# Make all letters lower case
	$title = lc($title);
	
	# lists everything that isn't a space or a letter and takes it out
	$title =~ s/[^\s\w]*//g;
	
	# If it is a letter, choose it over a number
	if ($title =~ /^([a-z ]+)$/){ 
		# add song title to biGram
		myBiGram($biGram, $1); 
		# keep track of the number of words in the title
		$counter++; 
	}
}

print "The count of the title is: " . $counter . "\n";

# Close the file handle
close INFILE; 

# At this point (hopefully) you will have finished processing the song 
# title file and have populated your data structure of bigram counts.
print "File parsed. Bigram model built.\n\n";

# User control loop
print "Enter a word [Enter 'q' to quit]: ";
$input = <STDIN>;
chomp($input);
print "\n";
	
while ($input ne "q"){
	print "\n\n";
	my ($mcw, $counter) = mcw($input);
	print "mcw($input) was:\n" . $mcw . "\n$counter\n";
	print "titleOfSong($input) was:\n" . titleOfSong($input) . "\n\n\n";
	print "Following words($input) was\n" . counterTracker($input) . "\n\n";	
	print "Enter a word [Enter 'q' to quit]: ";
	$input = <STDIN>;
	chomp($input);
	print "\n";	
}

sub mcw {
	my ($word) = @_;
	my $biggestWord = 1;
	my $biggestValue = 1;

	# This gets the highest value in the array
	if (exists $biGram{$word}){ 
		foreach my $key (keys $biGram{$word}) {
			my $counter = $biGram{$word}{$key};
			
			# If the biggestValue is smaller than the counter, change it
			# If the biggestWord is smaller than the key, change it
			if ($counter > $biggestValue) {	
				$biggestValue = $counter;
				$biggestWord = $key;	
			} 
			
			# If the biggestValue is equal to the counter, randomly pick one
			elsif ($counter = $biggestValue) {	
				if (int(rand(2)) > 1) {
					$biggestValue = $counter;
					$biggestWord = $key;
				}
			}
		}
	} else {
		# makes the biggestWord blank if there isn't a value to it
		$biggestWord = ""; 
	}
	return $biggestWord, $biggestValue;
}

sub myBiGram {
	my ($biGram, $phraseIt) = @_;
	@myWordsArray = split(' ',$phraseIt);
	@myFilterArray = ("a","an","and","for","from","in","of","on","or","out","the","to","with", "you", "are");

	# Puts the filtered parameters into a hash map to be able to match them
	my %parameters = map { $_ => 1 } @myFilterArray;	
	for my $i (0 .. $#myWordsArray) {
		my $word = $myWordsArray[$i];
		
		if ($i < $#myWordsArray){
			# Makes it so any words that are filtered will not be added
			if(!exists($parameters{$myWordsArray[$i + 1]})){ 
				# adds to the counter for the bigram 
				$biGram{$word}{$myWordsArray[$i + 1]}++; 
			}
		}
	}
}

sub titleOfSong {
	# user starts the title of the song
	my ($word) = @_;
	my $i;
	my $title = $word;
	my $currentWord = $word;
	
	for ($i = 1; $i < 20; $i++) { 
		# Gets the next word
		($currentWord, $_) = mcw($currentWord);
		if ($currentWord) {
			$title = $title . " " . $currentWord;
		} else {
			break; 
		}
	}
	return $title;
}

sub counterTracker {
	my $counter = 0;
	my ($word) = @_;
	
	# This gets the highest value in the array
	if (exists $biGram{$word}){ 
		foreach my $key (keys $biGram{$word}) {
			$counter++;
		}
	}
	return $counter;
}