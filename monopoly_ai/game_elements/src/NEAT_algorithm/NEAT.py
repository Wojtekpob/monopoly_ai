"""
This file defines the NEATAI class, which integrates a Python-based AI using the NEAT algorithm into a C++ application.
The class uses pybind11 to interface with Python, allowing it to train the AI and get actions based on the game state.
The NEATAI class includes methods for training the AI with game states and retrieving an action based on the current game state.
It also manages the Python interpreter's lifecycle by initializing and finalizing it within the constructor and destructor.
The PYBIND11_MODULE macro creates a Python module named monopoly_ai_cpp, exposing the NEATAI class and its methods to Python.
Author: Mikołaj Sendybył
"""
import neat
import pickle

class MonopolyAI:
    def __init__(self, config_file):
        self.config = neat.Config(neat.DefaultGenome, neat.DefaultReproduction,
                                  neat.DefaultSpeciesSet, neat.DefaultStagnation,
                                  config_file)
        self.p = neat.Population(self.config)
        self.p.add_reporter(neat.StdOutReporter(True))
        self.stats = neat.StatisticsReporter()
        self.p.add_reporter(self.stats)
        self.p.add_reporter(neat.Checkpointer(1))

    def train(self, game_state, generations=50):
        def eval_genomes(genomes, config):
            for genome_id, genome in genomes:
                genome.fitness = 0
                net = neat.nn.FeedForwardNetwork.create(genome, config)
                action = self.decide_action(net, game_state)
                genome.fitness += self.evaluate_action(action, game_state)

        # winner = self.p.run(eval_genomes, generations)
        with open("best_monopoly.pickle", "wb") as f:
            pickle.dump(winner, f)

    def decide_action(self, net, game_state):
        # Extract relevant game state information
        money = game_state['money']
        position = game_state['position']
        properties = game_state['properties']

        # Prepare inputs for the neural network
        inputs = [money, position] + properties
        output = net.activate(inputs)
        decision = output.index(max(output))
        return decision

    def evaluate_action(self, action, game_state):
        # dodać ewauację stanu gry po wykonaniu akcji

        fitness = game_state['money'] + sum(game_state['properties']) * 100
        return fitness

    def test_best_network(self, game_state):
        with open("best_monopoly.pickle", "rb") as f:
            winner = pickle.load(f)
        winner_net = neat.nn.FeedForwardNetwork.create(winner, self.config)
        return self.decide_action(winner_net, game_state)

# Integracja z c++
def train_ai(config_file, game_states, generations=50):
    ai = MonopolyAI(config_file)
    ai.train(game_states, generations)

def get_action(config_file, game_state):
    ai = MonopolyAI(config_file)
    action = ai.test_best_network(game_state)
    return action
