//
//  pipeline.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/23/20.
//

#ifndef pipeline_hpp
#define pipeline_hpp

#include <vector>

#include "pipe.hpp"
#include "reader.hpp"

using std::vector;

template<class T>
class Pipeline {
private:
    vector<unique_ptr<PipeBase<T>>> pipes;

public:
    void add(unique_ptr<PipeBase<T>> p);
    void run(const T& dataObj);
};

#endif /* pipeline_hpp */
