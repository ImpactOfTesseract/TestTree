# TestTree
Test task for job qualification

TestTree application implements an abstract class BaseHolder which is inherited by IntHolder, CharArrayHolder and DoubleHolder classes.
Provided data structure allows for building trees of references to the base class BaseHolder.

Data structure should roughly look like this:

![screenshot1](https://github.com/ImpactOfTesseract/TestTree/blob/master/TestTree/TreeSerialForTestTask.png)

Application was written with the help of Qt, which allowed to built a pleasant looking and flexible interface.

![screenshot1](https://github.com/ImpactOfTesseract/TestTree/blob/master/TestTree/1.png)

Application allows for building single or multiple trees at the same time with the help of QTreeWidget, which supports multiple top level
items. You can append children or delete highlighted items. Application supports serialization to .txt file and deserialization from the .txt file while also handling possible exceptions. 

You can find a release version in "TestTree release" folder. It is shipped with "ExampleTree.txt" text file which contains an example of a tree structure built solely with the help of this application.

Warning! This application was not tested on a large set of different systems and it may require additional libraries. I will try to test it on the multitude of different systems as soon as possible and include as much vital libraries as this application may need.

Knowns issues: at this current moment application does not support Cyrillic characters.
