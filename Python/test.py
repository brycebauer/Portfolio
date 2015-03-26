# author Nathan Doll
from random import randint #import needed for random number generator
numberOfRounds = 0 #number of rounds played will be set to 1, 3, 5, 7, or 9
numberOfMoves = 0 #keeps track of number of moves made so that iterative bot and my bot can determine their moves
moves = [None] * 18 #creates array that is set to 18 because moves will never exceed 18 since 1 move per person times 2 people times 9(max) rounds equals 18
p1Wins = 0 #tracks number of wins for player 1
p2Wins = 0 #tracks number of wins for player 2
numberOfTies = 0 #tracks number of ties
p1 = None 
p2 = None

class Main: #main class basically runs the game
    def __init__(self):
        print "Welcome To The"
        print "Rock, Paper, Scissors, Lizard, Spock Game"
        print "Created by Nathan Doll"
        print ""
        print "Please Start By Selecting 2 players From The Following List"
        print "    (1) Human Player"
        print "    (2) Random Bot"
        print "    (3) Stupid Bot"
        print "    (4) Iterative Bot"
        print "    (5) Last Play Bot"
        print "    (6) Doll Bot"
        print ""
        self.player1Selected()
        self.player2Selected()
        print ""
        self.roundSelection()
        print "%s vs. %s: FIGHT!\n" % (p1.getName(), p2.getName())
        for i in range(0, numberOfRounds): #for loop for gameplay
            global moves
            global numberOfMoves
            print "Round %1.0f:" % (i+1)
            p1move = p1.play()
            moves[numberOfMoves] = p1move
            numberOfMoves = numberOfMoves + 1
            print "    Player 1 Chooses: %s" % (p1move.getName())
            p2move = p2.play()
            moves[numberOfMoves] = p2move
            numberOfMoves = numberOfMoves + 1
            print "    Player 2 Chooses: %s" % (p2move.getName())
            print p1move.compareTo(p2move.getName())
            print ""
        if p1Wins > p2Wins:
            print "%s has defeated %s with a score of %1.0f to %1.0f" % (p1.getName(), p2.getName(), p1Wins, p2Wins)
        elif p1Wins < p2Wins:
            print "%s has defeated %s with a score of %1.0f to %1.0f" % (p2.getName(), p1.getName(), p2Wins, p1Wins)
        else:
            print "The Game is a Tie %s won %1.0f time(s) %s won %1.0f time(s) and %1.0f ties" % (p1.getName(), p1Wins, p2.getName(), p2Wins, numberOfTies)
    def roundSelection(self): #selects and sets number of rounds
        try:
            selectRounds = int(raw_input("Choose Number Of Rounds 1, 3, 5, 7, or 9\n"))
        except ValueError:
            print "Invalid Choise Please Try Again"
            self.roundSelection()
        global numberOfRounds
        if selectRounds == 1:
            numberOfRounds = numberOfRounds + 1
        elif selectRounds == 3:
            numberOfRounds = numberOfRounds + 3
        elif selectRounds == 5:
            numberOfRounds = numberOfRounds + 5
        elif selectRounds == 7:
            numberOfRounds = numberOfRounds + 7
        elif selectRounds == 9:
            numberOfRounds = numberOfRounds + 9
        else:
            print "Invalid Choise Please Try Again"
            self.roundSelection()
    def player1Selected(self): #selects and sets player 1
        try:
            selection = int(raw_input("Select Player 1: "))
        except ValueError:
            print "Invalid Choise Please Try Again"
            self.player1Selected()
        global p1
        if selection == 1:
            p1 = Human(self.nameSelect(1))
        elif selection == 2:
            p1 = RandomBot('RandomBot')
        elif selection == 3:
            p1 = StupidBot('StupidBot')
        elif selection == 4:
            p1 = IterativeBot('IterativeBot')
        elif selection == 5:
            p1 = LastPlayBot('LastPlayBot')
        elif selection == 6:
            p1 = MyBot('MyBot')
        else:
            print "Invalid Choise Please Try Again"
            self.player1Selected()
    def player2Selected(self): #selects and sets player 2
        try:
            selection = int(raw_input("Select Player 2: "))
        except ValueError:
            print "Invalid Choise Please Try Again"
            self.player2Selected()
        global p2
        if selection == 1:
            p2 = Human(self.nameSelect(2))
        elif selection == 2:
            p2 = RandomBot('RandomBot')
        elif selection == 3:
            p2 = StupidBot('StupidBot')
        elif selection == 4:
            p2 = IterativeBot('IterativeBot')
        elif selection == 5:
            p2 = LastPlayBot('LastPlayBot')
        elif selection == 6:
            p2 = MyBot('MyBot')
        else:
            print "Invalid Choise Please Try Again"
            self.player2Selected()
    def nameSelect(self, playerNumber): #allows a player to pick a human name
        selection = raw_input("Please Type A Name For Player %s" % (playerNumber))
        return selection
        
        
class Player: #superclass of Human, and the bots
    def __init__(self, name):
        self.name = name
    def getName(self):
        return self.name
    def play(self):
        NotImplementedError("Not yet implemented")

class Human(Player): #user selects move each round
    def play(self):
        print "(1) : Rock"
        print "(2) : Paper"
        print "(3) : Scissors"
        print "(4) : Lizard"
        print "(5) : Spock"
        return self.choise()
    def choise(self):
        try:
            selection = int(raw_input("Please enter a number: "))
        except ValueError:
            print "Invalid Choise Please Try Again"
            self.choise()
        if selection == 1:
            return Rock('Rock')
        elif selection == 2:
            return Paper('Paper')
        elif selection == 3:
            return Scissors('Scissors')
        elif selection == 4:
            return Lizard('Lizard')
        elif selection == 5:
            return Spock('Spock')
        else:
            print "Invalid Choise Please Try Again"
            self.choise() 
              
class StupidBot(Player): #Always selects spock just like the characters of The Big Bang Theory
    def play(self):
        return Spock('Spock') #It's only logical
    
class RandomBot(Player): #Always chooses a random choise
    random = randint(1,5)
    def play(self):
        if self.random == 1:
            return Rock('Rock')
        elif self.random == 2:
            return Paper('Paper')
        elif self.random == 3:
            return Scissors('Scissors')
        elif self.random == 4:
            return Lizard('Lizard')
        else:
            return Spock('Spock')
        
class IterativeBot(Player): # goes in order by name of the game ie Rock,paper,scissors,lizard,spock
    def play(self):
        if numberOfMoves%10 == 0:
            return Rock('Rock')
        elif numberOfMoves%10 == 1:
            return Rock('Rock')
        elif numberOfMoves%10 == 2:
            return Paper('Paper')
        elif numberOfMoves%10 == 3:
            return Paper('Paper')
        elif numberOfMoves%10 == 4:
            return Scissors('Scissors')
        elif numberOfMoves%10 == 5:
            return Scissors('Scissors')
        elif numberOfMoves%10 == 6:
            return Lizard('Lizard')
        elif numberOfMoves%10 == 7:
            return Lizard('Lizard')
        else:
            return Spock('Spock')
        
class LastPlayBot(Player): #first move he 
    def play(self):
        if numberOfMoves == 0:
            random = randint(1,5)
            if random == 1:
                return Rock('Rock')
            elif random == 2:
                return Paper('Paper')
            elif random == 3:
                return Scissors('Scissors')
            elif random == 4:
                return Lizard('Lizard')
            else:
                return Spock('Spock')
        elif numberOfMoves == 1:
            random = randint(1,5)
            if random == 1:
                return Rock('Rock')
            elif random == 2:
                return Paper('Paper')
            elif random == 3:
                return Scissors('Scissors')
            elif random == 4:
                return Lizard('Lizard')
            else:
                return Spock('Spock')
        elif numberOfMoves == 2:
            return moves[1]
        else:
            return moves[numberOfMoves-3]
        
class MyBot(Player): #my bot will determine other players previous move and will choose one of the two options that would have beaten it
    def play(self):
        if numberOfMoves == 0:
            random = randint(1,5)
            if random == 1:
                return Rock('Rock')
            elif random == 2:
                return Paper('Paper')
            elif random == 3:
                return Scissors('Scissors')
            elif random == 4:
                return Lizard('Lizard')
            else:
                return Spock('Spock')
        elif numberOfMoves == 1:
            random = randint(1,5)
            if random == 1:
                return Rock('Rock')
            elif random == 2:
                return Paper('Paper')
            elif random == 3:
                return Scissors('Scissors')
            elif random == 4:
                return Lizard('Lizard')
            else:
                return Spock('Spock')
        elif numberOfMoves == 2:
            return self.defeat(moves[1].getName())
        else:
            return self.defeat(moves[numberOfMoves-3].getName())
    def defeat(self, moveToDefeat):
        if moveToDefeat == "Rock":
            random = randint(1,2)
            if random == 1:
                return Paper('Paper')
            else:
                return Spock('Spock')
        elif moveToDefeat == "Paper":
            random = randint(1,2)
            if random == 1:
                return Scissors('Scissors')
            else:
                return Lizard('Lizard')
        elif moveToDefeat == "Scissors":
            random = randint(1,2)
            if random == 1:
                return Spock('Spock')
            else:
                return Rock('Rock')
        elif moveToDefeat == "Lizard":
            random = randint(1,2)
            if random == 1:
                return Rock('Rock')
            else:
                return Scissors('Scissors')
        else:
            random = randint(1,2)
            if random == 1:
                return Lizard('Lizard')
            else:
                return Paper('Paper')
                
class Element: #superclass of the options
    def __init__(self, name):
        self.name = name
    def getName(self):
        return self.name
    def compareTo(self, p2):
        NotImplementedError("Not yet implemented")
            
class Rock(Element): #option rock
    Element("Rock")
    def compareTo(self, p2):
        global numberOfTies
        global p1Wins
        global p2Wins
        
        if(p2 == "Rock"):
            numberOfTies = numberOfTies + 1
            return "    Rock equals Rock\n    Tie"
        elif(p2 == "Paper"):
            p2Wins = p2Wins + 1
            return "    Paper covers Rock\n    Player 2 Wins"
        elif(p2 == "Scissors"):
            p1Wins = p1Wins + 1
            return "    Rock crushes Scissors\n    Player 1 Wins"
        elif(p2 == "Lizard"):
            p1Wins = p1Wins + 1
            return "    Rock crushes Lizard\n    Player 1 Wins"
        else:
            p2Wins = p2Wins + 1
            return "    Spock vaporizes Rock\n    Player 2 Wins"
            
class Paper(Element): #option paper
    def compareTo(self, p2):
        global numberOfTies
        global p1Wins
        global p2Wins
        if(p2 == "Rock"):
            p1Wins = p1Wins + 1
            return "    Paper covers Rock\n    Player 1 Wins"
        elif(p2 == "Paper"):
            numberOfTies = numberOfTies + 1
            return "    Paper equals Paper\n    Tie"
        elif(p2 == "Scissors"):
            p2Wins = p2Wins + 1
            return "    Scissors cuts Paper\n    Player 2 Wins"
        elif(p2 == "Lizard"):
            p2Wins = p2Wins + 1
            return "    Lizard eats Paper\n    Player 2 Wins"
        else:
            p1Wins = p1Wins + 1
            return "    Paper disproves Spock\n    Player 1 Wins"
            
class Scissors(Element): #option scissors
    def compareTo(self, p2):
        global numberOfTies
        global p1Wins
        global p2Wins
        if(p2 == "Rock"):
            p2Wins = p2Wins + 1
            return "    Rock crushes Scissors\n    Player 2 Wins"
        elif(p2 == "Paper"):
            p1Wins = p1Wins + 1
            return "    Scissors cuts Paper\n    Player 1 Wins"
        elif(p2 == "Scissors"):
            numberOfTies = numberOfTies + 1
            return "    Scissors equals Scissors\n    Tie"
        elif(p2 == "Lizard"):
            p1Wins = p1Wins + 1
            return "    Scissors decapitate Lizard\n    Player 1 Wins"
        else:
            p2Wins = p2Wins + 1
            return "    Spock smashes Scissors\n    Player 2 Wins"
            
class Lizard(Element): #option lizard
    def compareTo(self, p2):
        global numberOfTies
        global p1Wins
        global p2Wins
        if(p2 == "Rock"):
            p2Wins = p2Wins + 1
            return "    Rock crushes Lizard\n    Player 2 Wins"
        elif(p2 == "Paper"):
            p1Wins = p1Wins + 1
            return "    Lizard eats Paper\n    Player 1 Wins"
        elif(p2 == "Scissors"):
            p2Wins = p2Wins + 1
            return "    Scissors decapitate Lizard\n    Player 2 Wins"
        elif(p2 == "Lizard"):
            numberOfTies = numberOfTies + 1
            return "    Lizard equals Lizard\n    Tie"
        else:
            p1Wins = p1Wins + 1
            return "    Lizard poisons Spock\n    Player 1 Wins"
            
class Spock(Element): #option spock
    def compareTo(self, p2):
        global numberOfTies
        global p1Wins
        global p2Wins
        if(p2 == "Rock"):
            p1Wins = p1Wins + 1
            return "    Spock vaporizes Rock\n    Player 1 Wins"
        elif(p2 == "Paper"):
            p2Wins = p2Wins + 1
            return "    Paper disproves Spock\n    Player 2 Wins"
        elif(p2 == "Scissors"):
            p1Wins = p1Wins + 1
            return "    Spock smashes Scissors\n    Player 1 Wins"
        elif(p2 == "Lizard"):
            p2Wins = p2Wins + 1
            return "    Lizard poisons Spock\n    Player 2 Wins"
        else:
            numberOfTies = numberOfTies + 1
     
if __name__ == "__main__":
    Main()
