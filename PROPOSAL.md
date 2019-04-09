# Proposal
My idea for the final project is a neural network that learns to play snake without any prelabeled training data. In order to achieve this, I will use the snake game that was provided in openFrameworks for our final machine problem. It provides a good basis and will allow for easy control of the snake. Furthermore, it will also give me direct access to information about the game, think "score" and "food". There is no need to take a screenshot of every fram in order to get relative information, so definitely makes our job easier!

In order to control the snake, I plan on using a genetic algorithm to prune 20% of the lowest performing neural networks. Afterwards, I will provide some sort of minor modification to the neural network weights at random (this allows us to test hyperparameters and perform evolution on the NN), which will encourage the neural networks to continue evolution. By the theories proposed by Darwin, only the most fit will survive each generation. As such, after many generations of evolution (~1000 generations), we should get a neural network that performs fairly well.

In order to accomplish what we are looking to do, we need to give our neural nets a way to learn. In order to do this, we need to give them a way to learn about the world around them. Reusing the snake game provided for this past machine problem will make this task significantly easier. There are several things that our snake neural networks need to know about the world around them in order to have a chance of evolving and getting better at the game. Information that we should provide the snake includes: can the snake go straight, can the snake go left, can the snake go right, is food straight ahead, is food to the left, is food to the right. With this information, the snake should be able to eventually learn to eat food and grow bigger and score more points... allegedly.

Unfortunately, this is not exactly the case. We need to give the neural net snake some incentive in order to go around and find food. If we don't, the snale will learn that it can survive forever by looping in circles forever. To counteract this, we provide rewards. When the snake eats a block, we will give it 10 points (this is subject to change, based on experimentation). 

We also need to give our snake incentive to explore. After all, if the snake does not have incentive to explore and find food, it will never learn that food gives it extra reward! In order to overcome this, we will give our snake a small reward for going towards the food and "punish" it for turning away from food. To do this, we will give it 1 point for taking a step towards food and take away 1.5 points whenever the snake gets further away from the food block. Remember the problem of the snake going in circles? Taking away 1.5 points every time the snake moves away from the food solves this issue.

This is a rough outline of how to create a neural network for a snake game that learns to play without any training data using a genetic algorithm. It may not be the general AI that every ML scientist craves, but it is a good start to unsupervised Machine Learning.

# Libraries
  - openFrameworks (http://openframeworks.cc)
  - OpenNN (http://opennn.net)?
  - Caffe2 (https://caffe2.ai)?
  - tiny-dnn (https://github.com/tiny-dnn/tiny-dnn#examples)
# Links and References
  - OpenNN Documentation:
    - http://www.opennn.net/documentation/reference/class_open_n_n_1_1_genetic_algorithm.html
  - Designing a Genetic Algorithm with NN's:
    - https://becominghuman.ai/designing-ai-solving-snake-with-evolution-f3dd6a9da867
  - ANN Optimization using Genetic Algorithm:
    - https://towardsdatascience.com/artificial-neural-networks-optimization-using-genetic-algorithm-with-python-1fe8ed17733e
