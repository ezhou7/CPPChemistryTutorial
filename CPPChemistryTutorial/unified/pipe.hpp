//
//  pipe.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/23/20.
//

#ifndef pipe_hpp
#define pipe_hpp

#include <memory>

#include "molecule.hpp"
#include "readers/nre.hpp"
#include "readers/reader.hpp"

using std::make_unique;
using std::move;
using std::unique_ptr;

template<class T>
class PipeBase {
public:
    virtual void transform(const T& data) = 0;
};

template<class T, class V>
class Pipe : PipeBase<V> {
protected:
    T transformer;
};

template<class T, class V>
class AbstractReaderPipe : Pipe<AbstractReader<T>, V> {};

class NREReaderPipe : Pipe<NREReader, MolecularData> {
private:
    string filepath;

public:
    NREReaderPipe(const string& filepath) {
        this->filepath = filepath;
    }
    
    void transform(const MolecularData& data) {
        transformer.readFile(filepath);
    }
};

#endif /* pipe_hpp */
