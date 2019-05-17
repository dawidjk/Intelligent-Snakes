# Intelligent Snakes
---
## History
Snake is a game that has long been played by many, especially all of us old enough to remember what a flip phone is. Since the dawn of this era, Snake has been used as a pleasant way to perform the action of what some call "wasting time." What doesn't kill you makes you stronger, right? With ofIntelligentSnake, you no longer have to "waste time" by playing the game, you can simply watch the game play itself!

## Background
As a developer, I have always been intrigued by Machine Learning models and all that they can accomplish. As such, I found this CS 126 final project to be a fantastic way to self-learn some Machine Learning theory. My first step to becoming a snake charmer? Figure out where to start - what I want the structure to be like.

## Structure
Having no training data, I needed to figure out how to best train the snakes to perform well. Traditional supervised learning was not a feasible approach, so I decided to proceed with a Genetic Algorithm in order to optimize my neural networks. I provided the algorithm with 100 Snake playing Neural Networks (powered by tiny_dnn) to breed them through Darwin's theories in order to create the ultimate snake population. Each of the neural networks is a 3 layer fully connected convolutional network. The first layer has 6 inputs (is straight safe, is left safe, is right safe, is food straight, is food left, is food right). The middle layer consists of 5 hidden nodes and the output consists of 3 nodes (straight, left, right). And so, I set the snakes loose.

## Genetics
The key feature to a genetic algorithm is breeding. We take the top 10% of the highest scoring snakes and breed them by randomly exchanging the weights of each node between two parent networks. This forms two child networks. We replace each of the bottom 90% networks with the bred children. Occasionally (~3% chance), we introduce a mutation - a completely new and randomly generated weight. This prevents the breeding pool from stagnating, so there is always a new trait to be learned.

## Setup
  - Install Xcode
  - Clone project
  - Compile and run in Xcode

## Operations
  - Press '1' to save a generation of snakes
  - Press 'L' to load a previously saved snake generation

## Libraries
  - OpenFrameworks (http://openframeworks.cc)
  - tiny-dnn (https://github.com/tiny-dnn/tiny-dnn)
