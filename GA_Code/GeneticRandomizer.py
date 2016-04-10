"""

 GeneticRandomizer.py

  Created on: Mar 7, 2016
      Author: Lee

"""

random_delta_mask = lambda max_step_size, randomizer, song: (randomizer.randrange(max_step_size + 1) for i in range(chromo_len*len(song)*5))

"""
This class handles the randomization of Genetic Algorithm specific
perameters. 
"""

class GeneticRandomizer:

    def __init__(self, randomizer):
        self.randomizer = randomizer
        
    def get_prob(self):
        """
        Output: a random number between 0 and 100
        """
        return self.randomizer.randrange(0, 100)

    def get_crossover_point(self, pheno1, pheno2):
        """
        Output: a crossover point for both pheno1 and pheno2
        """
        return self.randomizer.randrange(min(pheno1.min_chromo_length, pheno2.min_chromo_length))

    def get_delta_mask(self, max_step_size, pheno, meta_data):
        return meta_data + [self.randomizer.randrange(-max_step_size, max_step_size + 1)
                                for i in range(pheno.num_genes * 5)]

    def sample_one_item(self, arg):
        """
        Output: 1 element, picked randomly from arg
        """
        return self.randomizer.sample(arg, 1)[0]
