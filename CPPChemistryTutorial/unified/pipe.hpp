//
//  pipe.hpp
//  CPPChemistryTutorial
//
//  Created by Ethan Zhou on 10/23/20.
//

#ifndef pipe_hpp
#define pipe_hpp

#include <memory>
#include <utility>

#include "atom.hpp"
#include "molecule.hpp"
#include "readers/atom.hpp"
#include "readers/hessian.hpp"
#include "readers/nre.hpp"
#include "readers/orbital.hpp"
#include "readers/reader.hpp"

using std::enable_if;
using std::is_base_of;
using std::make_unique;
using std::move;
using std::unique_ptr;

template<class T>
class PipeBase {
public:
    virtual void transform(T& data) = 0;
};

template<class T, class V>
class Pipe : public PipeBase<V> {
protected:
    T transformer;
};

template<typename T, class U, class V, typename enable_if<is_base_of<AbstractReader<U>, T>::value>::type* = nullptr>
class AbstractReaderPipe : public Pipe<T, V> {
protected:
    string filepath;
    
public:
    AbstractReaderPipe(const string& filepath) {
        this->filepath = filepath;
    }
};

class AtomReaderPipe : public AbstractReaderPipe<AtomReader, MatrixXf, MolecularData> {
public:
    AtomReaderPipe(const string& filepath) : AbstractReaderPipe(filepath) {}
    
    void transform(MolecularData& data) {
        MatrixXf m = transformer.readFile(filepath);
        
        data.natoms = (int) m.rows();
        data.zvals = m.row(0).cast<int>();
        data.coords = m.bottomRows(m.rows() - 1);

        for (int i = 0; i < m.cols(); i++) {
            data.masses(i) = atomicMasses[data.zvals(i)];
        }
    }
};

class HessianReaderPipe : public AbstractReaderPipe<HessianReader, MatrixXf, MolecularData> {
public:
    HessianReaderPipe(const string& filepath) : AbstractReaderPipe(filepath) {}
    
    void transform(MolecularData& data) {
        data.hessian = transformer.readFile(filepath);
    }
};

class NREReaderPipe : public AbstractReaderPipe<NREReader, double, MolecularData> {
public:
    NREReaderPipe(const string& filepath) : AbstractReaderPipe(filepath) {}
    
    void transform(MolecularData& data) {
        data.nre = transformer.readFile(filepath);
    }
};

class AOReaderPipe : AbstractReaderPipe<AOReader, MatrixXf, MolecularData> {
private:
    int dataType;
    
public:
    AOReaderPipe(const string& filepath, const int dataType) : AbstractReaderPipe(filepath) {
        this->dataType = dataType;
    }
    
    void transform(MolecularData& data) {
        MatrixXf m = transformer.readFile(filepath);
        switch (dataType) {
            case 0:
                data.S = m;
                break;
            
            case 1:
                data.T = m;
                break;
                
            case 2:
                data.V = m;
                break;
            
            default:
                break;
        }
    }
};

#endif /* pipe_hpp */
