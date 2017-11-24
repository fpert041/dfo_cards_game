//
//  dfo_game.cpp
//  dfo_cards_cpp
//
//  Created by Francesco Perticarari on 21/11/2017.
//  Copyright © 2017 agapeSoft. All rights reserved.
//


#include "dfo_game.h"

double print_num()
{
    return 0.0;
}


void Dfo_game::setup() {
    
    /* Set up the DFO object to have a the fitness function that we need */
    dfo.reset(
              new DFO(
                      [this](std::vector<double> p) {
                          int sumGroup0 = 0;
                          int prodGroup1 = 1;
                          
                          double fitness = 0;
                          
                          for(int i = 0; i<p.size(); ++i) {
                              if(p[i] < 0.5) {
                                  sumGroup0 += i+1;
                              } else {
                                  prodGroup1 *= i+1;
                              }
                          }
                          
                          int errG0 = abs(sumGroup0 - 36)*10;
                          int errG1 = abs(prodGroup1 - 360);
                          
                          fitness = errG1 + errG0;
                          
                          return fitness;
                          
                      }
                      )
              );
    // set up a populatin size of 80
    dfo->popSize = 80;
    
    // set up a dimensionality of 10
    dfo->dim = 10;
    
    // set the range of all the dimensions of the search space
    dfo->searchSpaceWidth = std::vector<int>(dfo->dim, 1);
    
    // set neighbour-best algorithm rather swarm-best version (which would be prone to fall into local minima)
    dfo->democracy = true;
    
    //---------------------------
    
    // generate the swarm
    dfo->generateSwarmBin();
    

}

void Dfo_game::run() {

    // run the algorithm 50 times
    for (int i = 0; i<50; ++i){
        dfo->updateSwarm();
        std::cout << "cycle: " << i+1 << std::endl;
        std::cout << "best fly index: " << dfo->bestIndex << std::endl;
        std::cout << "best fly location: " << dfo->swarm[dfo->bestIndex]->toString() << std::endl;
        std::cout << "fitness: "<< dfo->swarm[dfo->bestIndex]->getFitness() << std::endl;
        std::cout << "---" << std::endl;
    }

    
}
