/**
*-------------------------------------------------
*  Copyright 2016 by Tidop Research Group <daguilera@usal.se>
*
* This file is part of GRAPHOS - inteGRAted PHOtogrammetric Suite.
*
* GRAPHOS - inteGRAted PHOtogrammetric Suite is free software: you can redistribute
* it and/or modify it under the terms of the GNU General Public
* License as published by the Free Software Foundation, either
* version 3 of the License, or (at your option) any later version.
*
* GRAPHOS - inteGRAted PHOtogrammetric Suite is distributed in the hope that it will
* be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*
* @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
*-------------------------------------------------
*/
#ifndef MICMACEOREADER_H
#define MICMACEOREADER_H

#include <QString>
#include <QDomElement>

#include "ExternalOrientation.h"

namespace PW{

/*!
 \brief The class MicMacEOReader provides reading functions for MICMAC External Orientation files.

*/
class LIBPWSHARED_EXPORT MicMacEOReader: public QObject
{
public:
/*!
 \brief

*/
    MicMacEOReader();
    ExteriorOrientation * read(QString filePath);
    ExteriorOrientation * read(QDomElement& root);


private:


};
}
#endif // MICMACEOREADER_H
