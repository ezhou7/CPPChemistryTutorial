//
//  TestPipeline.m
//  TestCPPChemistryTutorial
//
//  Created by Ethan Zhou on 11/12/20.
//

#import <XCTest/XCTest.h>

#import "pipeline.hpp"

@interface TestPipeline : XCTestCase

@end

@implementation TestPipeline

- (void)testAddPipe {
    auto nreReaderPipe = make_unique<NREReaderPipe>("");
    Pipeline<MolecularData> pipeline;
    
    pipeline.add(move(nreReaderPipe));
}

- (void)testRunPipeline {
    MolecularData molecularData;
    Pipeline<MolecularData> pipeline;
    
    const string project_path([PROJECT_DIR UTF8String]);
    const string relative_path = "/ProgrammingProjects/Project#03/input/h2o/STO-3G/enuc.dat";
    const string filepath = project_path + relative_path;

    auto nreReaderPipe = make_unique<NREReaderPipe>(filepath);
    pipeline.add(move(nreReaderPipe));
    
    pipeline.run(molecularData);
    
    XCTAssertEqualWithAccuracy(molecularData.nre, 8.002367, 0.0000001);
}

@end
