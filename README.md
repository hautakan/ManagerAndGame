# Arduino based Manager and a murder mystery game
This is a live action murder mystery game that resembles Werewolf, Mafioso, AmongUs, Dracula and other games where one player is a traitor and others try to catch him. Arduino project is for a Manager that can distribute tasks to players, counts time and plays a sound when a workshift (round) ends. You don't need it to play the game but if you like to build stuff ... have fun!

<img src="https://github.com/hautakan/ManagerAndGame/blob/main/TheManager-malli.png?raw=true" width="400">

# To build the Manager you will need
- Arduino UNO
- LCD screen (I used the one that comes with Arduino started kit, 16x2)
- Four digit display (I used TM1637)
- A button
- Piezo, if you want it to make a sound
- Powersource (I used a power bank with 5V / 2.1A output to make the Manager portable)

# How the Manager works and how to set it up
- The first screen should guide the player to press the button down and keep it pressed. The tasks are only displayed when the button is kept pressed down.
- Tasks are given to players randomly. They are currently such that they match my game area. Please edit the them to your liking. There are examples in the rules.
- You can set work shift length in the beginning of the code. A good length to start with is four minutes if you have 10+ players, 3 minutes if you have less.
- When the first player presses the button, the timer starts to count down. 
- When the timer reaches zero, a sound is played and timer resets to original shift length. 
- A new work shift begins again when a player presses the button.

# Included are also
- game rules in Finnish
- game rules in English
- .DXF files for making a box with a lasercutter from 3mm acrylic or what ever you want to use. I did not include a hole for installing the button, because your button might be different size than what I used. 

To be done:
Diagrams for the connections. 
