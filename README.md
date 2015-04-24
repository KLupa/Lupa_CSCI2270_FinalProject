# Lupa_CSCI2270_FinalProject
Kristian Lupa's CSCI2270 Final project

Project Summary:
This project is an addition to the spring 2015 CSCI2270 Assignment 8, which implemented a graph of "city" objects. The idea is that there is a zombie apocalypse, and that not all cities are accessible from all other cities. The functions already written in the assignment include: 'Print all cities', 'Find districts', 'Find shortest path', and 'Find shortest distance'. To the Graph class I added methods to add cities, delete cities, check cities for zombie infestation, change the infestation level of cities, calculate chance of survival in traveling between to cities (survival chance is based upon distance traveled and infestation status of cities visited along the way), and sort the cities either aplhabetically or by their district ID. The idea of this program is to help a survivor in this fantasy world to keep track of the state of the country, and to help make decisions regarding travel around the country.

How to Run:
When the main.cpp driver file is run, it should read the zombieCities.txt file and build an intitial graph of the cities in the file. The user will then be shown a menu, and the program will wait for a response. The response should be a a number corresponding to the option desired from the menu. The program will continue to display the menu after each operation until the 'quit' option is selected, at which point the program will terminate. The user may select any option any number of times, but the program may break if the input does not match the prompt from the program.

Dependencies:
None

System Requirements:
None

Group Members:
Kristian Lupa

Contributors:


Open issues/Bugs:

-Make districtinfestation more dynamic, as of now it is hard-coded to accept a max of 5 districts

-Add general error checking on user inputs to avoid error.
