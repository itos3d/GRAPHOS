#include <QDir>
#include "AsiftProcess.h"
#include "ASIFTkpd.h"
#include "ASIFTkpdConcurrent.h"
#include "ASIFTmactching.h"
#include "AsiftToPastisProcess.h"
#include "MultiProcessConcurrent.h"
//#include "Tools/ConvertProcess.h"
#include "ConvertProcess2.h"

using namespace PW;

AsiftProcess::AsiftProcess(QList<PWImage *> inputImages, QString outputPath, bool resize, int tilts):
    MultiProcess(true),
    mInputImages(inputImages)
{
    QStringList fullPaths;
    QString aFilename = inputImages.at(0)->getFileName();
    QString extension = aFilename.right(aFilename.length()-aFilename.lastIndexOf(".")-1);

    //Convert to png?
    if(extension.toLower() != "png"){
//        for (int i=0; i<inputImages.count(); i++){
//            QString pngFilePath = inputImages.at(i)->getFullPath();
//            pngFilePath = pngFilePath.left(pngFilePath.lastIndexOf(".")+1)
//                    + "png";
//            appendProcess(new ConvertProcess(inputImages.at(i)->getFullPath(),
//                                             pngFilePath));
//            fullPaths.append(pngFilePath);
//        }

        QStringList inputImagePaths;
        for (int i=0; i<inputImages.count(); i++){
            inputImagePaths.append(inputImages.at(i)->getFullPath());
            QString pngFilePath = inputImages.at(i)->getFullPath();
            pngFilePath = pngFilePath.left(pngFilePath.lastIndexOf(".")+1)
                    + "png";

            fullPaths.append(pngFilePath);


        }
        appendProcess(new ConvertProcess2(inputImagePaths));

    }
    else{
        for (int i=0; i<inputImages.count(); i++){
            fullPaths.append(inputImages.at(i)->getFullPath());
        }
    }

    if (outputPath.isEmpty()){
        QString aFileName = fullPaths.at(0);
        outputPath = aFileName.left(aFileName.lastIndexOf(QRegExp("/"))+1);
    }

    // key points detection:
//    for (int i=0; i<inputImages.count(); i++){
//        appendProcess(new ASIFTkpd(fullPaths.at(i),"",resize,tilts));
//    }

    // key points detection:

    appendProcess(new ASIFTkpdConcurrent(fullPaths,"",resize,tilts));

    // matchings:
    MultiProcessConcurrent *concurrentMatching = new MultiProcessConcurrent(false);

    for (int i=0; i < inputImages.count(); i++){
        QDir outputDir(outputPath+"/"+"Pastis"+inputImages.at(i)->getFileName());
        if (!outputDir.exists())
            outputDir.mkdir(outputPath+"/"+"Pastis"+inputImages.at(i)->getFileName());

        for (int j = i+1; j< inputImages.count(); j++){
            concurrentMatching->appendProcess(new ASIFTmactching(fullPaths.at(i) ,fullPaths.at(j),
                                             outputDir.absolutePath() + "/" + inputImages.at(j)->getFileName() + "_V.png",
                                             outputDir.absolutePath() + "/" + inputImages.at(j)->getFileName() + "_H.png",
                                             outputDir.absolutePath()+ "/" + inputImages.at(j)->getFileName() + ".txt"
                                             ));
        }
    }
    appendProcess(concurrentMatching);
    for (int i=0; i < inputImages.count(); i++){
        QDir outputDir(outputPath+"/"+"Pastis"+inputImages.at(i)->getFileName());
        for (int j = i+1; j< inputImages.count(); j++){
            // reverse matchings:
            QDir reverseOutputDir(outputPath+"/"+"Pastis"+inputImages.at(j)->getFileName());
            if (!reverseOutputDir.exists())
                reverseOutputDir.mkdir(outputPath+"/"+"Pastis"+inputImages.at(j)->getFileName());
            appendProcess(new AsiftToPastisProcess(outputDir.absolutePath()+ "/" + inputImages.at(j)->getFileName() + ".txt",
                                                   outputDir.absolutePath()+ "/" + inputImages.at(j)->getFileName() + ".txt",
                                                   reverseOutputDir.absolutePath() + "/" + inputImages.at(i)->getFileName() + ".txt"));
        }
    }

//    // matchings:

//    for (int i=0; i < inputImages.count(); i++){
//        QDir outputDir(outputPath+"/"+"Pastis"+inputImages.at(i)->getFileName());
//        if (!outputDir.exists())
//            outputDir.mkdir(outputPath+"/"+"Pastis"+inputImages.at(i)->getFileName());

//        for (int j = i+1; j< inputImages.count(); j++){
//            appendProcess(new ASIFTmactching(fullPaths.at(i) ,fullPaths.at(j),
//                                             outputDir.absolutePath() + "/" + inputImages.at(j)->getFileName() + "_V.png",
//                                             outputDir.absolutePath() + "/" + inputImages.at(j)->getFileName() + "_H.png",
//                                             outputDir.absolutePath()+ "/" + inputImages.at(j)->getFileName() + ".txt"
//                                             ));
//        }
//        for (int j = i+1; j< inputImages.count(); j++){
//            // reverse matchings:
//            QDir reverseOutputDir(outputPath+"/"+"Pastis"+inputImages.at(j)->getFileName());
//            if (!reverseOutputDir.exists())
//                reverseOutputDir.mkdir(outputPath+"/"+"Pastis"+inputImages.at(j)->getFileName());
//            appendProcess(new AsiftToPastisProcess(outputDir.absolutePath()+ "/" + inputImages.at(j)->getFileName() + ".txt",
//                                                   outputDir.absolutePath()+ "/" + inputImages.at(j)->getFileName() + ".txt",
//                                                   reverseOutputDir.absolutePath() + "/" + inputImages.at(i)->getFileName() + ".txt"));
//        }
//    }
}
