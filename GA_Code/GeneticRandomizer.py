random_delta_mask = lambda max_step_size, randomizer, song: (randomizer.randrange(max_step_size + 1) for i in range(chromo_len*len(song)*5))

class GeneticRandomizer:

    def __init__(self, randomizer):
        self.randomizer = randomizer
        
    def get_prob(self):
        return self.randomizer.randrange(0, 100)

    def get_crossover_point(self, pheno1, pheno2):
        return self.randomizer.randrange(min(pheno1.min_chromo_length, pheno2.min_chromo_length))

    def get_delta_mask(self, max_step_size, pheno, meta_data):
        return meta_data + [self.randomizer.randrange(-max_step_size, max_step_size + 1)
                                for i in range(pheno.num_genes * 5)]

    def sample_one_item(self, arg):
        return self.randomizer.sample(arg, 1)[0]
