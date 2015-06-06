var user = prompt("You are wandering on a path through a forest and suddenly the path branches into three different directions. One goes RIGHT, one goes LEFT, and the last one goes FORWARD. Which path do you choose?").toLowerCase();

switch(user) {
    case 'right':
        console.log("The path to the right took you to a cave. You notice that there is a torch and a sword next to the entrance of the cave.");
        var choice = prompt("Do you want to enter?")
        if (choice === "yes"){
            var prepare = prompt("Do you want to grab the sword and torch?");
            console.log("Upon entering the cave, you grab the sword and torch in anticipation of a fight. The air gets hotter the farther you walk in the cave. After walking for a while, you notice a bright light in the distance. Intrigued with this light you continue walking towards the light. While getting closer you notice the light is in a room full of gold and a dragon. You need to fight the dragon to get the treasure and escape the cave.")
            var hits = Math.floor(Math.random()*2);
            if (prepare === "yes" && hits === 1){
                console.log("Congrats You have slain the dragon! You take as much gold as you can carry and go back to your house. Upon returning to your house, everyone in the town is there and cheers for you. You and your fellow townsmen celebrate the slaying of the dragon. The town deicded to erect a statue of you with your sword in the dragons dead body, so that anyone who visits the town will know of your brave conquest.")
            }
            else if (prepare === "yes" && hits < 1){
                console.log("You start to fight the dragon. After hours of going blow for blow with the dragon, you start to get tired and start to miss hitting the dragon. Before you know it the dragons claw slashes through your body and you drop your sword. With one last breath, you see the dragon curl up into a ball and go back to sleep. As time went on the town noticed your absence and went looking for you. A group of hunters enter the cave an find your body in a dried pool of blood. The dragon awakes to the sound of the hunters enter the room. The hunters defeat the dragon and take the gold along with your body. The town decides to use the gold to better the town and erect a statue to remember you as a brave fighter");
            }
            else {
                console.log("The dragon instantly kills you and goes back to sleep to await another encounter with an adventurer.");
            }
        }
        break;
    case 'left':
        console.log("The path to the left took you to a lake where you see a FISHING POLE, a SWORD, or a BOW with some arrows in a quiver.");
        var lakeCh = prompt("Which do you choose?").toLowerCase();
        if (lakeCh === "sword" || lakeCh === "bow"){
            console.log("As you approach the lake you notice that the middle of a lake is bubbling. You notice the water is starting to get darker. All of the sudden a bunch of tenticles pop out of the lake and start to head toward you. With you weapon you decide to fight the monster.")
            var attack = prompt("Do you attack 5 or 10 times?");
            var monster = Math.random()*attack;
            var total = Math.random()*attack;
            if (total >= monster){
                console.log("You have defeated the giant squid. As the squids dead carcass sinks to the bottom of the lake, you feel the ground shake. To your right a cave entrance emerges from the ground. Upon entering the cave there is a glimmer that catches your eye. In the room that the glimmer came from you notice it is full of treasure. You grab as much as you can and return to your house. The word of you slaying the monster has reached your home village and they held a feast in your honor.")
            }
            else {
                console.log("After fighting for a while, you start to feel tired. You collapse due to exhaustion and a tenticle starts to come towards you. The tenticle pulls into the water and with one last breath you see yourself surrounded by water.")
            }
        }
        else {
            console.log("It is a nice day and you decide to go fishing. After a few hours, you feel a tug on the line. You start to reel whatever is on the line. Then all of the sudden a tenticle pops out of the lake and wraps around you. The tenticle pulls into the water and with one last breath you see yourself surrounded by water.");
        }
        break;
    case 'forward':
        console.log("You continue on the path that is in front of you. This path leads you to a cliff. you notice that there is climbing gear next to you.");
        var climb = prompt("Do you want to take it and climb the cliff?");
        var wind = Math.random()*100;
        if (climb === "yes" && wind >= 50){
            console.log("You start your climb and about half way up the wind starts to pick up. You decide to continue on thinking that this will just be a slight breeze. After a few minutes the wind get worse. Suddenly the wind rips you off the side of the cliff and you fall to your death.");
        }
        else if (climb === "yes" && wind < 50){
            console.log("You start your climb and about half way up the wind starts to pick up. You decide to continue since this is just a slight breeze. You climb to the top of the cliff and turn around to see a beautiful scene of the mountains, lake, and forest. After admiring the scene you decide to build a house up there and live the rest of your life.");
        }
        else {
            console.log("You decide that it is too windy to climb, so you go back to your house. You turn on the tv when you get back and there is a story of a horrific accident that happened at the cliffs due to feirce winds. You feel bad for the people that died, but feel blessed that you decided to not to climb.");
        }
        break;
    default:
        console.log("You got back to your house since you didn't choose to go left, right, or forward. While at your house you turn the TV on and there is a news story about a treasure that was found in a cave in the forest that you were going to go on an adventure in. Upon hearing this you wish that there was a curse on the treasure because you chickened out on the adventure that you were about to go on.");
        break;
}