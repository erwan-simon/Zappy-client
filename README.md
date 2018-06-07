# Zappy-client

## Abstract

Zappy is a tool allowing to build artificial intelligence scripts to make beeings evolve in an artificial world.

## The Zappy Project

### General Presentation

The Zappy Project is a revival of a school project I wanted to make because I didn't fully acheived what I wanted to do back then.
It consists in the creation of an artificial world where artificials beeings (a.k.a. players) can live.
The main purpose of this remake is to build a base tool that will allow me to train to build Artificial Intelligence and see where it gets me.

You have 3 submodules to this project, each of them communicating via unix sockets :

#### The Server

The server is the main actor if this project. It hosts all the game mechanics. Only him has the knowledge of the "rules", how the game means to be played.

#### The Client

The client will connect to the server and represent a player, a beeing in the artificial world. Like anyone of us, humans, it doesn't have any obvious purpose other than survive.
The AI script will lie in this part.

#### The Graphics

The graphics purpose is to monitor the players' peregrination in the artificial world.

### Protocol

The Zappy project implement its own "RFC". The server, client and graphics parts use a specific protocol when exchanging datas.


| 		            | Description                                   | Target   | Arguments                  |
|-------------------|-----------------------------------------------|----------|----------------------------|
| Common protocol   |                                               |          |                            |
| 1                 | OK                                            | /        | None                       |
| 2                 | Error                                         | /        | None                       |
| 3                 | Exit                                          | /        | None                       |
|                   |                                               |          |                            |
| Server protocol   |                                               |          |                            |
| 100               | Server accept client or graphics connection   | /        | array of map size          |
| 101               | Server sends the board                        | Graphics | A tripple dimensions array |
| 102               | Server sends a part of the board              | Client   | A double dimensions array  |
| 103               | Server sends inventory                        | /        | An array                   |
|                   |                                               |          |                            |
| Client protocol   |                                               |          |                            |
| 200               | Client starts communication with the server   | server   | None                       |
| 210               | Message                                       | server   | A string                   |
| 220               | Move left                                     | server   | None                       |
| 221               | Move right                                    | server   | None                       |
| 222               | Move up                                       | server   | None                       |
| 223               | Move down                                     | server   | None                       |
| 230               | Pick                                          | server   | A string                   |
|                   |                                               |          |                            |
|                   |                                               |          |                            |
| Graphics protocol |                                               |          |                            |
| 300               | Graphics starts communication with the server | server   | None                       |
| 301               | Graphics asks for the board                   | server   | None                       |

## The client

### Requirements

 - Linux
 - G++

### How-To-Use-It

First compile the sources to generate the binary file. At the root of the repository, launch in a shell :
```
make
```

Then execute the binary file and give it a port number :
```
./client 5555
```
