#include <vtkSTLReader.h>
#include <vtkExtractEdges.h>
#include <vtkTubeFilter.h>
#include <vtkSTLWriter.h>
#include <vtkSmartPointer.h>

#define vsp(className, name)\
  vtkSmartPointer<className> name;\
  name = vtkSmartPointer<className>::New();\

int main( int argc, char** argv )
{
  vsp( vtkSTLReader, reader );
  vsp( vtkExtractEdges, edges );
  vsp( vtkTubeFilter, tube );
  vsp( vtkSTLWriter, writer );



}
