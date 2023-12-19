Namespaces :

* Every class should be a part of the 'di' namespace
* Every 'user class' should be a part of the 'di' namespace
* Every 'internal class' should be a part of the 'di::internal' namespace
* Namespace names MUST start with a lower case letter, and the coding style is snake_case
* Every INTERNAL namespace must have its header(.h/.hpp) and implementation file(.cpp). The internal namespaces are OPTIONAL !
  Naming convention of the files will be : Di + entire namespace path as CamelCase. Example : DiInternalImage.h/cpp DiInternalFile.h/cpp
  Being a "category", the namespace must contain its own common structs/enums/etc.Having only one "common" "declaration files pair"" will contaminate the library.
* Keep the folder hierarchy of your project(or the VisualStudio folder tree), as following :
  - Have a folder for each namespace
  - Have an 'impl' folder for each namespace folder ALWAYS
  - Have an 'internal' folder for each namespace ALWAYS (except for the folders named 'internal')
  Note : On a "namespace folder", only the header files should appear... And several sub-folders. You are interested in header files usually, isn't it ?

User-defined classes : 

* MUST use the RAII idiom
* Interfaces must be prefixed with a capital 'i' ('I')
* Abstract classes must NOT use the previous convention

Header files :

* All headers MUST have include guards, please DO NOT use "#pragma once". The include guard should be of format : __CLASS_NAME_H__
* All classes MUST be AT LEAST inside the 'di' namespace
* If you don't want to expose some classes/declarations, consider moving them inside the 'di::internal' namespace. Forget about the 'pImplm' idiom.
* All class names MUST start with "Di", except interfaces.
* All class names MUST have the 'CamelCase' format
* All method names, except constructors/destructors MUST respect the 'pascalCase' format
* IMPORTANT : A "copy-paste" example based on the rule of five and a completion of the coding guidelines is provided inside the di::DiTestClass.

Source Files : 

* No special constraints

Namespaces list: 
  - di
  - di::internal
  - di::file
  - di::file::internal
  - di::image
  - di::image::internal

The library has the following capabilities : 
  - File path manipulation(DiFileInfo)
  - Binary and text files manipulation(DiFile used as DiTextFile or DiBinaryFile)
  - Some degree of Bitmap and Png file manipulation, for Icon files usage(DiIconFile is used for icon files manipulation and IGenericImage is used to create a DiBmpFile or DiPngFile)
  - All 'non-internal' classes are following the RAII idiom