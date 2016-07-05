#include <vtkSTLReader.h>
#include <vtkExtractEdges.h>
#include <vtkTubeFilter.h>
#include <vtkSTLWriter.h>
#include <vtkSmartPointer.h>

#include "yaap/yaap.h"

#define vsp(className, name)\
  vtkSmartPointer<className> name;\
  name = vtkSmartPointer<className>::New();\

int main( int argc, char** argv )
{
  yaap::Parser parser( argc, argv );

  yaap::OptionArg<std::string>* inFileOpt = parser.AddOptionArg<std::string>( 
    'i',
    "input-file",
    "STL input file name",
    1, 
    true );

  yaap::OptionArg<std::string>* outFileOpt = parser.AddOptionArg<std::string>(
    'o',
    "output-file",
    "STL output file name",
    1,
    true );
  
  yaap::OptionArg<int>* nbFacesOpt = parser.AddOptionArg<int>(
    'f',
    "faces",
    "Number of faces of the tubes (default to 3)",
    1);

  yaap::OptionArg<float>* radiusOpt = parser.AddOptionArg<float>(
    'r',
    "radius",
    "Radius of the tubes (default to 0.01)",
    1);

  yaap::Option* helpOpt = parser.AddOption( 'h', "help", "Display a brief help" );

  if( !parser.IsCommandLineValid() || helpOpt->Exists() || argc == 1 )
  {
    parser.Usage();
    return(EXIT_FAILURE);
  }

  float radius = 0.01;
  if( radiusOpt->Exists() )
  {
    radius = radiusOpt->GetValue();
  }

  int nbFaces = 3;
  if( nbFacesOpt->Exists() )
  {
    nbFaces = nbFacesOpt->GetValue();
  }

  std::string inFile = inFileOpt->GetValue();
  std::string outFile = outFileOpt->GetValue();

  vsp( vtkSTLReader, reader );
  vsp( vtkExtractEdges, edges );
  vsp( vtkTubeFilter, tube );
  vsp( vtkSTLWriter, writer );

  reader->SetFileName( inFile.c_str() );

  tube->SetVaryRadiusToVaryRadiusOff();
  tube->SetRadius( radius );
  tube->SetNumberOfSides( nbFaces );

  writer->SetFileName( outFile.c_str() );

  edges->SetInputConnection( reader->GetOutputPort() );
  tube->SetInputConnection( edges->GetOutputPort() );
  writer->SetInputConnection( tube->GetOutputPort() );

  writer->Write();

  return(EXIT_SUCCESS);
}
