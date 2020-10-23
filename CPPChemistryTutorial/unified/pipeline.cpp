//
//  pipeline.cpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/23/20.
//

#include "pipeline.hpp"

template<class T>
void Pipeline<T>::add(unique_ptr<PipeBase<T>> p) {
    pipes.push_back(move(p));
}

template<class T>
void Pipeline<T>::run(const T& dataObj) {
    for (auto pipe : pipes) {
        pipe->transform(dataObj);
    }
}
