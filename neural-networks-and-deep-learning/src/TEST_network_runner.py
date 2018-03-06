import mnist_loader
import network

training_data, validation_data, test_data = mnist_loader.load_data_wrapper()
net = network.Network([784, 30, 10]) # this means there is a 784 neuron input, 30 neuron hidden layer and 10 neuron output

net.SGD(training_data, 30, 10, 3.0, test_data = test_data)
