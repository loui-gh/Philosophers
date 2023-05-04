# Philosophers
The 42 Philosophers project gets students to solve the philosophers problem. The rules of this particular version are;
- each philosopher has a fork, each fork requires its own mutex
- the bowl of spaghetti is in the middle of the table
- philosophers need two forks to eat

# How I went about solving the problem
- I used a double-linked list to replicate a circular table 👩‍🔧

User input: ./philo [number of philosophers] [time to die] [time to eat] [time to sleep] [optional: number of meals before to stop]
