# Lupa_CSCI2270_FinalProject
Kristian Lupa's CSCI2270 Final project

Project Summary:
This project is an addition to the spring 2015 CSCI2270 Assignment 8, which implemented a graph of "city" objects. The idea is that there is a zombie apocalypse, and that not all cities are accessible from all other cities. The functions already written in the assignment include: 'Print all cities', 'Find districts', 'Find shortest path', and 'Find shortest distance'. To the Graph class I added methods to add cities, delete cities, check cities for zombie infestation, change the infestation level of cities, and calculate chance of survival in traveling between to cities (survival chance is based upon distance traveled and infestation status of cities visited along the way). The idea of this program is to help a survivor in this fantasy world to keep track of the state of the country, and to help make decisions regarding travel around the country.

How to Run:


Dependencies:


System Requirements:


Group Members:
Kristian Lupa

Contributors:


Open issues/Bugs:

-Issues with sequencing in deletecity. After deleting a city from vertices, the adjacency vectors get all out of whack and a very weird error occurs when print cities is called after deleting certain cities.

-Make districtinfestation more dynamic, as of now it is hard-coded to accept a max of 5 districts

-Will sorting vertices work? Same problem as deleting vertices? Adjacent pointers stay pointing to same spot but things in those spots move/get deleted. Will changing vertices to vertex* work? Or are these operations impossible?
