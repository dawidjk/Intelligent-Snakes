# Week 0
## In Progress
  - Understand how genetic algorithm works
  - Save all networks on button press
  - Load edited weights back into Neural Network
  - Break down code into more functional code blocks - especially breed parents
  
## Completed
  - Download OpenNN
  - Compile OpenNN
  - Test OpenNN library.
  - Download and setup ofSnake, which will be used as my snake plotform
  - Figuring out how to implement OpenNN with snake game
     - How to import .lib?
     - OpenNN has too little support and did not want to play nice with a vector a NN. As such, will switch to a different NN + library
   - Evaluate information provided by the snake game
   - OpenNN does not compile, removed
   - Download and compile tiny-dnn (better supported and documented)
     - Fixed naming and import conflicts 
  - Find a NN library that plays nicely with oFx
    - Using tiny_dnn as NN library of choice
  - Added starvation time for snake
  - Added loop penalty and kill off to prevent program from crashing
  - Fixed snake color generation
    - Original colors were often too bright to be visible and not painful to look at.
  - Implement a JSON library to edit Network weights
  - Created algorithm for breeding parents to produce children.
  - After each Generation, add mutation to percentage of Networks
