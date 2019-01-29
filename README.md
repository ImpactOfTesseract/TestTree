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

Knowns issues: at this current moment application does not support Cyrillic characters.
