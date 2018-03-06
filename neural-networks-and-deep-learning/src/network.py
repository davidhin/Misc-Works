"""
network.py
~~~~~~~~~~

A module to implement the stochastic gradient descent learning
algorithm for a feedforward neural network.  Gradients are calculated
using backpropagation.  Note that I have focused on making the code
simple, easily readable, and easily modifiable.  It is not optimized,
and omits many desirable features.
"""

#### Libraries
# Standard library
import random
import sys
import pprint

# Third-party libraries
import numpy as np

class Network(object):

    def __init__(self, sizes):
        self.num_layers = len(sizes)
        self.sizes = sizes
        self.biases = [np.random.randn(y, 1) for y in sizes[1:]]
        self.weights = [np.random.randn(y, x)
                        for x, y in zip(sizes[:-1], sizes[1:])]

    def feedforward(self, a):
        for b, w in zip(self.biases, self.weights):
            a = sigmoid(np.dot(w, a)+b)
        return a

    def SGD(self, training_data, epochs, mini_batch_size, eta,
            test_data=None):
        if test_data: n_test = len(test_data)
        n = len(training_data)
        for j in xrange(epochs):
            random.shuffle(training_data)
            mini_batches = [
                training_data[k:k+mini_batch_size]
                for k in xrange(0, n, mini_batch_size)]
            for mini_batch in mini_batches:
                self.update_mini_batch(mini_batch, eta)
            if test_data:
                print "Epoch {0}: {1} / {2}".format(
                    j, self.evaluate(test_data), n_test)
            else:
                print "Epoch {0} complete".format(j)

    def update_mini_batch(self, mini_batch, eta):
        unzipped_batch = zip(*mini_batch)
        x_matrix = np.column_stack(unzipped_batch[0])
        y_matrix = np.column_stack(unzipped_batch[1])
        nabla_b, nabla_w = self.backprop2(x_matrix, y_matrix)
        self.weights = [w-(eta/len(mini_batch))*nw
                        for w, nw in zip(self.weights, nabla_w)]
        self.biases = [b-(eta/len(mini_batch))*nb
                       for b, nb in zip(self.biases, nabla_b)]

    def backprop2(self, x, y):
        nabla_b = [np.zeros(b.shape) for b in self.biases]
        nabla_w = [np.zeros(w.shape) for w in self.weights]
        ### 1. Feedforward
        activation = x
        activations = [x] # List to store matrices with columns representing
                          # activations of each sample in mini batch.
                          # Matrices represent the layer. 
        zs = [] # store matrices with columns representing weighted
                # inputs of each sample in the mini_batch
        for b, w in zip(self.biases, self.weights):
            z = np.dot(w, activation) + b
            zs.append(z)
            activation = sigmoid(z)
            activations.append(activation)
        ### 2. Compute error (delta) for output layer
        delta_samples = np.multiply(self.cost_derivative(activations[-1], y), sigmoid_prime(zs[-1]))
        nabla_b[-1] = np.matrix(delta_samples.sum(axis=1)).reshape(len(delta_samples),1)
        nabla_w[-1] = np.dot(delta_samples, activations[-2].transpose())
        ### 3. Backpropagate
        for l in xrange(2, self.num_layers):
            z = zs[-l]
            sp = sigmoid_prime(z)
            delta_samples = np.multiply(np.dot(self.weights[-l+1].transpose(), delta_samples), sp)
            nabla_b[-l] = np.matrix(delta_samples.sum(axis=1)).reshape(len(delta_samples),1)
            nabla_w[-l] = np.dot(delta_samples, activations[-l-1].transpose())
        return (nabla_b, nabla_w)

    def evaluate(self, test_data):
        test_results = [(np.argmax(self.feedforward(x)), y)
                        for (x, y) in test_data]
        return sum(int(x == y) for (x, y) in test_results)

    def cost_derivative(self, output_activations, y):
        return (output_activations-y)

#### Miscellaneous functions
def sigmoid(z):
    return 1.0/(1.0+np.exp(-z))

def sigmoid_prime(z):
    return np.multiply(sigmoid(z), (1-sigmoid(z)))
