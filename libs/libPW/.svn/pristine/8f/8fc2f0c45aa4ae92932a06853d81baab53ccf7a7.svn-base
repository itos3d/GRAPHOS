//--------------------------------------------------------------------------------
//    Copyright (c) Kate Labs Ltd 2010-2011
//
//    This file is part of QImageMetaData.
//
//    QImageMetaData is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    QImageMetaData is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with QImageMetaData. If not, see <http://www.gnu.org/licenses/>.
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
// Headers
//--------------------------------------------------------------------------------
#include <QtCore/QDebug>
#include <QtCore/QStringList>

#include "QImageMetaData.h"

#include "QImageMetaDataRational.h"

//--------------------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------------------
QImageMetaData::QImageMetaData()
{
  errorCode_ = ErrorCodeUndefined;

  endianness_ = QDataStream::LittleEndian;

  baseOffset_ = 0;

  tiffValid_ = false;

  tiffOffset_ = 0;

  imageFormat_ = ImageFormatUndefined;

  imageDescription_ = "Not defined";
  make_             = "Not defined";
  model_            = "Not defined";
  artist_           = "Not defined";

  width_  = 0;
  length_ = 0;

  focalLength35mm_ = 0;

  compression_ = CompressionUndefined;

  photometric_ = PhotometricUndefined;

  planar_ = PlanarUndefined;

  resolution_ = ResolutionUndefined;

  orientation_ = OrientationUndefined;

  samples_ = 0;

  software_ = "Not defined";

  dateAndTime_                    = "Not defined";
  dateAndTimeSubseconds_          = "Not defined";

  dateAndTimeOriginal_            = "Not defined";
  dateAndTimeOriginalSubseconds_  = "Not defined";

  dateAndTimeDigitized_           = "Not defined";
  dateAndTimeDigitizedSubseconds_ = "Not defined";

  flash_ = 0;

  flashStatus_   = FlashStatusUndefined;
  flashStrobe_   = FlashStrobeUndefined;
  flashMode_     = FlashModeUndefined;
  flashFunction_ = FlashFunctionUndefined;
  flashRedEye_   = FlashRedEyeUndefined;

  exposureProgram_ = ExposureProgramUndefined;

  lightSource_ = LightSourceUndefined;

  copyright_ = "";

  colorSpace_ = ColorSpaceUndefined;

  pixelXDimension_  = 0;
  pixelYDimension_  = 0;

  gainControl_ = GainControlUndefined;

  sensingMethod_ = SensingMethodUndefined;

  customRendered_ = CustomRenderedUndefined;

  exposureMode_ = ExposureModeUndefined;

  whiteBalance_ = WhiteBalanceUndefined;

  sceneCaptureType_ = SceneCaptureTypeUndefined;

  contrast_ = ContrastUndefined;

  saturation_ = SaturationUndefined;

  sharpness_ = SharpnessUndefined;

  subjectDistanceRange_ = SubjectDistanceRangeUndefined;

  yCbCrPositioning_ = YCbCrPositioningUndefined;

  focalPlaneResolution_ = ResolutionUndefined;

  meteringMode_ = MeteringModeUndefined;

  documentName_ = "Not defined";
  pageName_     = "Not defined";

  hostComputer_ = "Not defined";

  rowsPerStrip_ = 0;

  cellWidth_  = 0;
  cellLength_ = 0;

  tileWidth_  = 0;
  tileLength_ = 0;

  relatedSoundFile_ = "Not defined";

  imageUniqueID_ = "Not defined";

  thresholding_ = 1;

  fillOrder_ = 1;

  grayResponseUnit_ = 2;

  T4Options_ = 0;
  T6Options_ = 0;

  predictor_ = 1;

  spectralSensitivity_ = "Not defined";

  inkSet_ = 1;

  inkNames_ = "Not defined";

  numberOfInks_ = 4;

  targetPrinter_ = "Not defined";

  exifVersion_     = "Not defined";
  flashPixVersion_ = "Not defined";

  //------------------------------------------------------------------------------
  // GPS tags
  //------------------------------------------------------------------------------
  gpsLatitudeRef_  = GPSLatitudeUndefined;
  gpsLongitudeRef_ = GPSLongitudeUndefined;

  gpsAltitudeRef_ = GPSAltitudeUndefined;

  gpsSatellites_  = "Not defined";

  gpsStatus_      = GPSStatusUndefined;
  gpsMeasureMode_ = GPSMeasureModeUndefined;

  gpsSpeedRef_ = GPSSpeedUndefined;
  gpsTrackRef_ = GPSDirectionUndefined;

  gpsImgDirectionRef_ = GPSDirectionUndefined;

  gpsMapDatum_ = "Not defined";

  gpsDestLatitudeRef_  = GPSLatitudeUndefined;
  gpsDestLongitudeRef_ = GPSLongitudeUndefined;
  gpsDestBearingRef_   = GPSDirectionUndefined;
  gpsDestDistanceRef_  = GPSDistanceUndefined;

  gpsDateStamp_ = "Not defined";

  gpsDifferential_ = GPSDifferentialUndefined;

  //------------------------------------------------------------------------------
  // XMP tags
  //------------------------------------------------------------------------------
  lens_         = "Not defined";
  serialNumber_ = "Not defined";

  //------------------------------------------------------------------------------
  // Generic
  //------------------------------------------------------------------------------
  stringLimit_  = 65535;
  genericLimit_ = 65535;

  errorMessage_ = "";

  warningLimit_ = 10;
  warningCount_ =  0;

  //------------------------------------------------------------------------------
  // XMP metadata debugging information
  //------------------------------------------------------------------------------
  debugXMPName_ = "";
  debugXMPText_ = "";
}

//--------------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------------
QImageMetaData::~QImageMetaData()
{

}

//--------------------------------------------------------------------------------
// Copy constructor
//--------------------------------------------------------------------------------
QImageMetaData::QImageMetaData(const QImageMetaData& obj)
{
  errorCode_ = obj.errorCode_;

  endianness_ = obj.endianness_;

  baseOffset_ = obj.baseOffset_;

  tiffValid_ = obj.tiffValid_;

  tiffOffset_ = obj.tiffOffset_;

  errorMessage_ = obj.errorMessage_;

  warningLimit_ = obj.warningLimit_;
  warningCount_ = obj.warningCount_;

  imageFormat_ = obj.imageFormat_;

  definedTags_ = obj.definedTags_;

  unsupportedTags_ = obj.unsupportedTags_;

  iTXtChunks_ = obj.iTXtChunks_;

  iTXtSizes_ = obj.iTXtSizes_;

  imageDescription_ = obj.imageDescription_;
  make_             = obj.make_;
  model_            = obj.model_;
  artist_           = obj.artist_;

  width_  = obj.width_;
  length_ = obj.length_;
  depth_  = obj.depth_;

  exposureTime_    = obj.exposureTime_;
  shutterSpeed_    = obj.shutterSpeed_;
  fNumber_         = obj.fNumber_;
  aperture_        = obj.aperture_;
  ISOSpeedRatings_ = obj.ISOSpeedRatings_;
  focalLength_     = obj.focalLength_;

  focalLength35mm_  = obj.focalLength35mm_;

  compression_ = obj.compression_;

  photometric_ = obj.photometric_;

  samples_ = obj.samples_;

  xResolution_ = obj.xResolution_;
  yResolution_ = obj.yResolution_;

  planar_ = obj.planar_;

  resolution_ = obj.resolution_;

  orientation_ = obj.orientation_;

  software_ = obj.software_;

  dateAndTime_           = obj.dateAndTime_;
  dateAndTimeSubseconds_ = obj.dateAndTimeSubseconds_;

  dateAndTimeOriginal_            = obj.dateAndTimeOriginal_;
  dateAndTimeOriginalSubseconds_  = obj.dateAndTimeOriginalSubseconds_;

  dateAndTimeDigitized_           = obj.dateAndTimeDigitized_;
  dateAndTimeDigitizedSubseconds_ = obj.dateAndTimeDigitizedSubseconds_;

  exposureProgram_ = obj.exposureProgram_;

  lightSource_ = obj.lightSource_;

  flash_ = obj.flash_;

  flashStatus_   = obj.flashStatus_;
  flashStrobe_   = obj.flashStrobe_;
  flashMode_     = obj.flashMode_;
  flashFunction_ = obj.flashFunction_;
  flashRedEye_   = obj.flashRedEye_;

  copyright_ = obj.copyright_;

  colorSpace_ = obj.colorSpace_;

  pixelXDimension_ = obj.pixelXDimension_;
  pixelYDimension_ = obj.pixelYDimension_;

  digitalZoomRatio_ = obj.digitalZoomRatio_;

  gainControl_ = obj.gainControl_;

  sensingMethod_ = obj.sensingMethod_;

  customRendered_ = obj.customRendered_;

  exposureMode_ = obj.exposureMode_;

  whiteBalance_ = obj.whiteBalance_;

  sceneCaptureType_ = obj.sceneCaptureType_;

  contrast_ = obj.contrast_;

  saturation_ = obj.saturation_;

  sharpness_ = obj.sharpness_;

  subjectDistanceRange_ = obj.subjectDistanceRange_;

  yCbCrSubSampling_ = obj.yCbCrSubSampling_;

  yCbCrPositioning_ = obj.yCbCrPositioning_;

  brightness_ = obj.brightness_;

  focalPlaneXResolution_ = obj.focalPlaneXResolution_;
  focalPlaneYResolution_ = obj.focalPlaneYResolution_;

  focalPlaneResolution_ = obj.focalPlaneResolution_;

  meteringMode_ = obj.meteringMode_;

  documentName_ = obj.documentName_;
  pageName_     = obj.pageName_;

  hostComputer_ = obj.hostComputer_;

  rowsPerStrip_    = obj.rowsPerStrip_;
  stripOffsets_    = obj.stripOffsets_;
  stripByteCounts_ = obj.stripByteCounts_;

  cellWidth_  = obj.cellWidth_;
  cellLength_ = obj.cellLength_;

  tileWidth_  = obj.tileWidth_;
  tileLength_ = obj.tileLength_;

  tileOffsets_    = obj.tileOffsets_;
  tileByteCounts_ = obj.tileByteCounts_;

  compressedBitsPerPixel_ = obj.compressedBitsPerPixel_;

  relatedSoundFile_ = obj.relatedSoundFile_;

  imageUniqueID_ = obj.imageUniqueID_;

  thresholding_ = obj.thresholding_;

  fillOrder_ = obj.fillOrder_;

  minSampleValue_ = obj.minSampleValue_;
  maxSampleValue_ = obj.maxSampleValue_;

  xPosition_ = obj.xPosition_;
  yPosition_ = obj.yPosition_;

  freeOffsets_    = obj.freeOffsets_;
  freeByteCounts_ = obj.freeByteCounts_;

  grayResponseUnit_  = obj.grayResponseUnit_;
  grayResponseCurve_ = obj.grayResponseCurve_;

  T4Options_ = obj.T4Options_;
  T6Options_ = obj.T6Options_;

  pageNumber_ = obj.pageNumber_;

  transferFunction_ = obj.transferFunction_;

  predictor_ = obj.predictor_;

  whitePoint_            = obj.whitePoint_;
  primaryChromaticities_ = obj.primaryChromaticities_;

  colorMap_      = obj.colorMap_;
  halfToneHints_ = obj.halfToneHints_;

  spectralSensitivity_ = obj.spectralSensitivity_;

  subjectDistance_ = obj.subjectDistance_;

  subjectArea_ = obj.subjectArea_;

  flashEnergy_ = obj.flashEnergy_;

  subjectLocation_ = obj.subjectLocation_;

  exposureIndex_ = obj.exposureIndex_;

  inkSet_ = obj.inkSet_;

  inkNames_ = obj.inkNames_;

  numberOfInks_ = obj.numberOfInks_;

  dotRange_ = obj.dotRange_;

  targetPrinter_ = obj.targetPrinter_;

  extraSamples_ = obj.extraSamples_;

  sampleFormat_ = obj.sampleFormat_;

  transferRange_ = obj.transferRange_;

  yCbCrCoefficients_ = obj.yCbCrCoefficients_;

  referenceBlackWhite_ = obj.referenceBlackWhite_;

  exifVersion_ = obj.exifVersion_;

  flashPixVersion_ = obj.flashPixVersion_;

  componentsConfiguration_ = obj.componentsConfiguration_;

  //------------------------------------------------------------------------------
  // GPS tags
  //------------------------------------------------------------------------------
  gpsVersion_ = obj.gpsVersion_;

  gpsLatitudeRef_ = obj.gpsLatitudeRef_;
  gpsLatitude_    = obj.gpsLatitude_;

  gpsLongitudeRef_ = obj.gpsLongitudeRef_;
  gpsLongitude_    = obj.gpsLongitude_;

  gpsAltitudeRef_ = obj.gpsAltitudeRef_;
  gpsAltitude_    = obj.gpsAltitude_;

  gpsTimeStamp_ = obj.gpsTimeStamp_;

  gpsSatellites_  = obj.gpsSatellites_;
  gpsStatus_      = obj.gpsStatus_;
  gpsMeasureMode_ = obj.gpsMeasureMode_;

  gpsDOP_ = obj.gpsDOP_;

  gpsSpeedRef_ = obj.gpsSpeedRef_;
  gpsSpeed_    = obj.gpsSpeed_;

  gpsTrackRef_ = obj.gpsTrackRef_;
  gpsTrack_    = obj.gpsTrack_;

  gpsImgDirectionRef_ = obj.gpsImgDirectionRef_;
  gpsImgDirection_    = obj.gpsImgDirection_;

  gpsMapDatum_ = obj.gpsMapDatum_;

  gpsDestLatitudeRef_ = obj.gpsDestLatitudeRef_;
  gpsDestLatitude_    = obj.gpsDestLatitude_;

  gpsDestLongitudeRef_ = obj.gpsDestLongitudeRef_;
  gpsDestLongitude_    = obj.gpsDestLongitude_;

  gpsDestBearingRef_ = obj.gpsDestBearingRef_;
  gpsDestBearing_    = obj.gpsDestBearing_;

  gpsDestDistanceRef_ = obj.gpsDestDistanceRef_;
  gpsDestDistance_    = obj.gpsDestDistance_;

  gpsDateStamp_ = obj.gpsDateStamp_;

  gpsDifferential_ = obj.gpsDifferential_;

  //------------------------------------------------------------------------------
  // XMP tags
  //------------------------------------------------------------------------------
  lens_         = obj.lens_;
  serialNumber_ = obj.serialNumber_;

  //------------------------------------------------------------------------------
  // XMP metadata debugging information
  //------------------------------------------------------------------------------
  debugXMPName_ = obj.debugXMPName_;
  debugXMPText_ = obj.debugXMPText_;
}

//--------------------------------------------------------------------------------
// Copy assignment operator
//--------------------------------------------------------------------------------
QImageMetaData& QImageMetaData::operator=(const QImageMetaData& rhs)
{
  if (&rhs == this) {
    return *this;
  }

  errorCode_ = rhs.errorCode_;

  endianness_ = rhs.endianness_;

  baseOffset_ = rhs.baseOffset_;

  tiffValid_ = rhs.tiffValid_;

  tiffOffset_ = rhs.tiffOffset_;

  errorMessage_ = rhs.errorMessage_;

  warningLimit_ = rhs.warningLimit_;
  warningCount_ = rhs.warningCount_;

  imageFormat_ = rhs.imageFormat_;

  definedTags_ = rhs.definedTags_;

  unsupportedTags_ = rhs.unsupportedTags_;

  iTXtChunks_ = rhs.iTXtChunks_;

  iTXtSizes_ = rhs.iTXtSizes_;

  imageDescription_ = rhs.imageDescription_;
  make_             = rhs.make_;
  model_            = rhs.model_;
  artist_           = rhs.artist_;

  width_  = rhs.width_;
  length_ = rhs.length_;
  depth_  = rhs.depth_;

  exposureTime_     = rhs.exposureTime_;
  shutterSpeed_     = rhs.shutterSpeed_;
  fNumber_          = rhs.fNumber_;
  aperture_         = rhs.aperture_;
  ISOSpeedRatings_  = rhs.ISOSpeedRatings_;
  focalLength_      = rhs.focalLength_;

  focalLength35mm_  = rhs.focalLength35mm_;

  compression_ = rhs.compression_;

  photometric_ = rhs.photometric_;

  samples_ = rhs.samples_;

  xResolution_ = rhs.xResolution_;
  yResolution_ = rhs.yResolution_;

  planar_ = rhs.planar_;

  resolution_ = rhs.resolution_;

  orientation_ = rhs.orientation_;

  software_ = rhs.software_;

  dateAndTime_           = rhs.dateAndTime_;
  dateAndTimeSubseconds_ = rhs.dateAndTimeSubseconds_;

  dateAndTimeOriginal_            = rhs.dateAndTimeOriginal_;
  dateAndTimeOriginalSubseconds_  = rhs.dateAndTimeOriginalSubseconds_;

  dateAndTimeDigitized_           = rhs.dateAndTimeDigitized_;
  dateAndTimeDigitizedSubseconds_ = rhs.dateAndTimeDigitizedSubseconds_;

  exposureProgram_ = rhs.exposureProgram_;

  lightSource_ = rhs.lightSource_;

  flash_ = rhs.flash_;

  flashStatus_   = rhs.flashStatus_;
  flashStrobe_   = rhs.flashStrobe_;
  flashMode_     = rhs.flashMode_;
  flashFunction_ = rhs.flashFunction_;
  flashRedEye_   = rhs.flashRedEye_;

  copyright_ = rhs.copyright_;

  colorSpace_ = rhs.colorSpace_;

  pixelXDimension_ = rhs.pixelXDimension_;
  pixelYDimension_ = rhs.pixelYDimension_;

  digitalZoomRatio_ = rhs.digitalZoomRatio_;

  gainControl_ = rhs.gainControl_;

  sensingMethod_ = rhs.sensingMethod_;

  customRendered_ = rhs.customRendered_;

  exposureMode_ = rhs.exposureMode_;

  whiteBalance_ = rhs.whiteBalance_;

  sceneCaptureType_ = rhs.sceneCaptureType_;

  contrast_ = rhs.contrast_;

  saturation_ = rhs.saturation_;

  sharpness_ = rhs.sharpness_;

  subjectDistanceRange_ = rhs.subjectDistanceRange_;

  yCbCrSubSampling_ = rhs.yCbCrSubSampling_;

  yCbCrPositioning_ = rhs.yCbCrPositioning_;

  brightness_ = rhs.brightness_;

  focalPlaneXResolution_ = rhs.focalPlaneXResolution_;
  focalPlaneYResolution_ = rhs.focalPlaneYResolution_;

  focalPlaneResolution_ = rhs.focalPlaneResolution_;

  meteringMode_ = rhs.meteringMode_;

  documentName_ = rhs.documentName_;
  pageName_     = rhs.pageName_;

  hostComputer_ = rhs.hostComputer_;

  rowsPerStrip_    = rhs.rowsPerStrip_;
  stripOffsets_    = rhs.stripOffsets_;
  stripByteCounts_ = rhs.stripByteCounts_;

  cellWidth_  = rhs.cellWidth_;
  cellLength_ = rhs.cellLength_;

  tileWidth_  = rhs.tileWidth_;
  tileLength_ = rhs.tileLength_;

  tileOffsets_    = rhs.tileOffsets_;
  tileByteCounts_ = rhs.tileByteCounts_;

  compressedBitsPerPixel_ = rhs.compressedBitsPerPixel_;

  relatedSoundFile_ = rhs.relatedSoundFile_;

  imageUniqueID_ = rhs.imageUniqueID_;

  thresholding_ = rhs.thresholding_;

  fillOrder_ = rhs.fillOrder_;

  minSampleValue_ = rhs.minSampleValue_;
  maxSampleValue_ = rhs.maxSampleValue_;

  xPosition_ = rhs.xPosition_;
  yPosition_ = rhs.yPosition_;

  freeOffsets_    = rhs.freeOffsets_;
  freeByteCounts_ = rhs.freeByteCounts_;

  grayResponseUnit_  = rhs.grayResponseUnit_;
  grayResponseCurve_ = rhs.grayResponseCurve_;

  T4Options_ = rhs.T4Options_;
  T6Options_ = rhs.T6Options_;

  pageNumber_ = rhs.pageNumber_;

  transferFunction_ = rhs.transferFunction_;

  predictor_ = rhs.predictor_;

  whitePoint_            = rhs.whitePoint_;
  primaryChromaticities_ = rhs.primaryChromaticities_;

  colorMap_      = rhs.colorMap_;
  halfToneHints_ = rhs.halfToneHints_;

  spectralSensitivity_ = rhs.spectralSensitivity_;

  subjectDistance_ = rhs.subjectDistance_;

  subjectArea_ = rhs.subjectArea_;

  flashEnergy_ = rhs.flashEnergy_;

  subjectLocation_ = rhs.subjectLocation_;

  exposureIndex_ = rhs.exposureIndex_;

  inkSet_ = rhs.inkSet_;

  inkNames_ = rhs.inkNames_;

  numberOfInks_ = rhs.numberOfInks_;

  dotRange_ = rhs.dotRange_;

  targetPrinter_ = rhs.targetPrinter_;

  extraSamples_ = rhs.extraSamples_;

  sampleFormat_ = rhs.sampleFormat_;

  transferRange_ = rhs.transferRange_;

  yCbCrCoefficients_ = rhs.yCbCrCoefficients_;

  referenceBlackWhite_ = rhs.referenceBlackWhite_;

  exifVersion_ = rhs.exifVersion_;

  flashPixVersion_ = rhs.flashPixVersion_;

  componentsConfiguration_ = rhs.componentsConfiguration_;

  //------------------------------------------------------------------------------
  // GPS tags
  //------------------------------------------------------------------------------
  gpsVersion_ = rhs.gpsVersion_;

  gpsLatitudeRef_ = rhs.gpsLatitudeRef_;
  gpsLatitude_    = rhs.gpsLatitude_;

  gpsLongitudeRef_ = rhs.gpsLongitudeRef_;
  gpsLongitude_    = rhs.gpsLongitude_;

  gpsAltitudeRef_ = rhs.gpsAltitudeRef_;
  gpsAltitude_    = rhs.gpsAltitude_;

  gpsTimeStamp_ = rhs.gpsTimeStamp_;

  gpsSatellites_  = rhs.gpsSatellites_;
  gpsStatus_      = rhs.gpsStatus_;
  gpsMeasureMode_ = rhs.gpsMeasureMode_;

  gpsDOP_ = rhs.gpsDOP_;

  gpsSpeedRef_ = rhs.gpsSpeedRef_;
  gpsSpeed_    = rhs.gpsSpeed_;

  gpsTrackRef_ = rhs.gpsTrackRef_;
  gpsTrack_    = rhs.gpsTrack_;

  gpsImgDirectionRef_ = rhs.gpsImgDirectionRef_;
  gpsImgDirection_    = rhs.gpsImgDirection_;

  gpsMapDatum_ = rhs.gpsMapDatum_;

  gpsDestLatitudeRef_ = rhs.gpsDestLatitudeRef_;
  gpsDestLatitude_    = rhs.gpsDestLatitude_;

  gpsDestLongitudeRef_ = rhs.gpsDestLongitudeRef_;
  gpsDestLongitude_    = rhs.gpsDestLongitude_;

  gpsDestBearingRef_ = rhs.gpsDestBearingRef_;
  gpsDestBearing_    = rhs.gpsDestBearing_;

  gpsDestDistanceRef_ = rhs.gpsDestDistanceRef_;
  gpsDestDistance_    = rhs.gpsDestDistance_;

  gpsDateStamp_ = rhs.gpsDateStamp_;

  gpsDifferential_ = rhs.gpsDifferential_;

  //------------------------------------------------------------------------------
  // XMP tags
  //------------------------------------------------------------------------------
  lens_         = rhs.lens_;
  serialNumber_ = rhs.serialNumber_;

  //------------------------------------------------------------------------------
  // XMP metadata debugging information
  //------------------------------------------------------------------------------
  debugXMPName_ = rhs.debugXMPName_;
  debugXMPText_ = rhs.debugXMPText_;

  return *this;
}

//--------------------------------------------------------------------------------
// Error code
//--------------------------------------------------------------------------------
QImageMetaData::ErrorCode QImageMetaData::errorCode() {
  return errorCode_;
}

//--------------------------------------------------------------------------------
// Read - unsigned rational
//--------------------------------------------------------------------------------
QImageMetaDataRational<quint32> QImageMetaData::readRational(QIODevice& data,quint32 offset) {
  //------------------------------------------------------------------------------
  // Rational
  //------------------------------------------------------------------------------
  QImageMetaDataRational<quint32> rational;

  //------------------------------------------------------------------------------
  // Current
  //------------------------------------------------------------------------------
  qint64 current = data.pos();

  //------------------------------------------------------------------------------
  // Offset
  //------------------------------------------------------------------------------
  data.seek(static_cast<qint64>(offset) + baseOffset_);

  //------------------------------------------------------------------------------
  // Input stream
  //------------------------------------------------------------------------------
  QDataStream* input = new QDataStream(&data);

  input->setByteOrder(endianness_);

  //------------------------------------------------------------------------------
  // Nominator and denominator
  //------------------------------------------------------------------------------
  quint32 temp;

  *input >> temp;

  rational.setNominator(temp);

  *input >> temp;

  rational.setDenominator(temp);

  //------------------------------------------------------------------------------
  // Current
  //------------------------------------------------------------------------------
  data.seek(current);

  //------------------------------------------------------------------------------
  // Return
  //------------------------------------------------------------------------------
  return rational;
}

//--------------------------------------------------------------------------------
// Read - signed rational
//--------------------------------------------------------------------------------
QImageMetaDataRational<qint32> QImageMetaData::readSRational(QIODevice& data,quint32 offset)
{
  //------------------------------------------------------------------------------
  // Return
  //------------------------------------------------------------------------------
  QImageMetaDataRational<qint32> rational;

  //------------------------------------------------------------------------------
  // Current
  //------------------------------------------------------------------------------
  qint64 current = data.pos();

  //------------------------------------------------------------------------------
  // Offset
  //------------------------------------------------------------------------------
  data.seek(static_cast<qint64>(offset) + baseOffset_);

  //------------------------------------------------------------------------------
  // Input stream
  //------------------------------------------------------------------------------
  QDataStream* input = new QDataStream(&data);

  input->setByteOrder(endianness_);

  //------------------------------------------------------------------------------
  // Nominator and denominator
  //------------------------------------------------------------------------------
  qint32 temp;

  *input >> temp;

  rational.setNominator(temp);

  *input >> temp;

  rational.setDenominator(temp);

  //------------------------------------------------------------------------------
  // Current
  //------------------------------------------------------------------------------
  data.seek(current);

  //------------------------------------------------------------------------------
  // Return
  //------------------------------------------------------------------------------
  return rational;
}

//------------------------------------------------------------------------------
// Read - array of unsigned rationals
//------------------------------------------------------------------------------
QVector< QImageMetaDataRational<quint32> > QImageMetaData::readRationalArray(QIODevice& data,quint32 count,quint32 offset)
{
  //------------------------------------------------------------------------------
  // Array
  //------------------------------------------------------------------------------
  QVector< QImageMetaDataRational<quint32> > result;

  //------------------------------------------------------------------------------
  // Current
  //------------------------------------------------------------------------------
  qint64 current = data.pos();

  //------------------------------------------------------------------------------
  // Offset
  //------------------------------------------------------------------------------
  data.seek(static_cast<qint64>(offset) + baseOffset_);

  //------------------------------------------------------------------------------
  // Input stream
  //------------------------------------------------------------------------------
  QDataStream* input = new QDataStream(&data);

  input->setByteOrder(endianness_);

  //------------------------------------------------------------------------------
  // Array
  //------------------------------------------------------------------------------
  quint32 temp;

  QImageMetaDataRational<quint32>* aux;

  for (unsigned int i = 0;i < count;++i) {
    aux = new QImageMetaDataRational<quint32>();

    *input >> temp;

    aux->setNominator(temp);

    *input >> temp;

    aux->setDenominator(temp);

    result.append(*aux);
  }

  //------------------------------------------------------------------------------
  // Current
  //------------------------------------------------------------------------------
  data.seek(current);

  //------------------------------------------------------------------------------
  // Return
  //------------------------------------------------------------------------------
  return result;
}

//------------------------------------------------------------------------------
// Read - array of signed rationals
//------------------------------------------------------------------------------
QVector< QImageMetaDataRational<qint32> > QImageMetaData::readSRationalArray(QIODevice& data,quint32 count,quint32 offset)
{
  //------------------------------------------------------------------------------
  // Array
  //------------------------------------------------------------------------------
  QVector< QImageMetaDataRational<qint32> > result;

  //------------------------------------------------------------------------------
  // Current
  //------------------------------------------------------------------------------
  qint64 current = data.pos();

  //------------------------------------------------------------------------------
  // Offset
  //------------------------------------------------------------------------------
  data.seek(static_cast<qint64>(offset) + baseOffset_);

  //------------------------------------------------------------------------------
  // Input stream
  //------------------------------------------------------------------------------
  QDataStream* input = new QDataStream(&data);

  input->setByteOrder(endianness_);

  //------------------------------------------------------------------------------
  // Array
  //------------------------------------------------------------------------------
  qint32 temp;

  QImageMetaDataRational<qint32>* aux;

  for (unsigned int i = 0;i < count;++i) {
    aux = new QImageMetaDataRational<qint32>();

    *input >> temp;

    aux->setNominator(temp);

    *input >> temp;

    aux->setDenominator(temp);

    result.append(*aux);
  }

  //------------------------------------------------------------------------------
  // Current
  //------------------------------------------------------------------------------
  data.seek(current);

  //------------------------------------------------------------------------------
  // Return
  //------------------------------------------------------------------------------
  return result;
}

//------------------------------------------------------------------------------
// Read - array
//------------------------------------------------------------------------------
QVector<quint32> QImageMetaData::readArray(QIODevice& data,quint32 type,quint32 count,quint32 offset)
{
  //------------------------------------------------------------------------------
  // Array
  //------------------------------------------------------------------------------
  QVector<quint32> result;

  //------------------------------------------------------------------------------
  // Auxiliary variables
  //------------------------------------------------------------------------------
  quint8  valueByte;
  quint16 valueShort;
  quint32 valueLong;

  //------------------------------------------------------------------------------
  // Current
  //------------------------------------------------------------------------------
  qint64 current = data.pos();

  //------------------------------------------------------------------------------
  // Offset
  //------------------------------------------------------------------------------
  if (this->byteCount(type,count) > 4) {
    data.seek(static_cast<qint64>(offset) + baseOffset_);

  //------------------------------------------------------------------------------
  // Value
  //------------------------------------------------------------------------------
  } else {
    data.seek(data.pos() - 4);

  }

  //------------------------------------------------------------------------------
  // Input stream
  //------------------------------------------------------------------------------
  QDataStream* input = new QDataStream(&data);

  input->setByteOrder(endianness_);

  //------------------------------------------------------------------------------
  // Values
  //------------------------------------------------------------------------------
  for (unsigned int i = 0;i < count;++i) {
    //----------------------------------------------------------------------------
    // Byte
    //----------------------------------------------------------------------------
    if (type == 1 || type == 7) {
      *input >> valueByte;

      result.append(valueByte);

    //----------------------------------------------------------------------------
    // Short
    //----------------------------------------------------------------------------
    } else if (type == 3) {
      *input >> valueShort;

      result.append(valueShort);

    //----------------------------------------------------------------------------
    // Long
    //----------------------------------------------------------------------------
    } else if (type == 4) {
      *input >> valueLong;

      result.append(valueLong);

    }
  }

  //------------------------------------------------------------------------------
  // Current
  //------------------------------------------------------------------------------
  data.seek(current);

  //------------------------------------------------------------------------------
  // Return
  //------------------------------------------------------------------------------
  return result;
}

//--------------------------------------------------------------------------------
// readString
//--------------------------------------------------------------------------------
QString QImageMetaData::readString(QIODevice& data,quint32 count,quint32 offset)
{
  //------------------------------------------------------------------------------
  // Current
  //------------------------------------------------------------------------------
  qint64 current = data.pos();

  //------------------------------------------------------------------------------
  // Offset
  //------------------------------------------------------------------------------
  if (count > 4) {
    data.seek(static_cast<qint64>(offset) + baseOffset_);
  } else {
    data.seek(data.pos() - 4);
  }

  //------------------------------------------------------------------------------
  // Input stream
  //------------------------------------------------------------------------------
  QDataStream* input = new QDataStream(&data);

  //------------------------------------------------------------------------------
  // String
  //------------------------------------------------------------------------------
  QString result;

  quint8 value;

  QChar temp;

  //------------------------------------------------------------------------------
  // The end character is ignored, because QString is applied!
  //------------------------------------------------------------------------------
  for (unsigned int i = 0;i < count;++i) {
    *input >> value;

    temp = QChar(value);

    if (!temp.isNull())
      result.append(value);
  }

  //------------------------------------------------------------------------------
  // Current
  //------------------------------------------------------------------------------
  data.seek(current);

  //------------------------------------------------------------------------------
  // Return
  //------------------------------------------------------------------------------
  return result;
}

//--------------------------------------------------------------------------------
// Read PNG chunk type
//--------------------------------------------------------------------------------
QImageMetaData::PNGType QImageMetaData::determinePNGType(quint32 type)
{
  //------------------------------------------------------------------------------
  // Values
  //------------------------------------------------------------------------------
  QVector<quint8> types;

  quint8 value;

  value = (0xFF000000 & type) >> 24;

  types.append(value);

  value = (0x00FF0000 & type) >> 16;

  types.append(value);

  value = (0x0000FF00 & type) >>  8;

  types.append(value);

  value = (0x000000FF & type);

  types.append(value);

  //------------------------------------------------------------------------------
  // Type
  //------------------------------------------------------------------------------
  if (types[0] ==  73 && types[1] == 72 && types[2] == 68 && types[3] ==  82) {
    return IHDR;
  } else if (types[0] ==  80 && types[1] == 76 && types[2] == 84 && types[3] ==  69) {
    return PLTE;
  } else if (types[0] ==  73 && types[1] == 68 && types[2] == 65 && types[3] ==  84) {
    return IDAT;
  } else if (types[0] ==  73 && types[1] == 69 && types[2] == 78 && types[3] ==  68) {
    return IEND;
  } else if (types[0] ==  98 && types[1] == 75 && types[2] == 71 && types[3] ==  68) {
    return bKGD;
  } else if (types[0] ==  99 && types[1] == 72 && types[2] == 82 && types[3] ==  77) {
    return cHRM;
  } else if (types[0] == 103 && types[1] == 65 && types[2] == 77 && types[3] ==  65) {
    return gAMA;
  } else if (types[0] == 104 && types[1] == 73 && types[2] == 83 && types[3] ==  84) {
    return hIST;
  } else if (types[0] == 105 && types[1] == 67 && types[2] == 67 && types[3] ==  80) {
    return iCCP;
  } else if (types[0] == 105 && types[1] == 84 && types[2] == 88 && types[3] == 116) {
    return iTXt;
  } else if (types[0] == 112 && types[1] == 72 && types[2] == 89 && types[3] == 115) {
    return pHYs;
  } else if (types[0] == 115 && types[1] == 66 && types[2] == 73 && types[3] ==  84) {
    return sBIT;
  } else if (types[0] == 115 && types[1] == 80 && types[2] == 76 && types[3] ==  84) {
    return sPLT;
  } else if (types[0] == 115 && types[1] == 82 && types[2] == 71 && types[3] ==  66) {
    return sRGB;
  } else if (types[0] == 116 && types[1] == 69 && types[2] == 88 && types[3] == 116) {
    return tEXt;
  } else if (types[0] == 116 && types[1] == 73 && types[2] == 77 && types[3] ==  69) {
    return tIME;
  } else if (types[0] == 116 && types[1] == 82 && types[2] == 78 && types[3] ==  83) {
    return tRNS;
  } else if (types[0] == 122 && types[1] == 84 && types[2] == 88 && types[3] == 116) {
    return zTXt;
  } else {
    qDebug() << "Unknown PNG chunk type" << types[0] << types[1] << types[2] << types[3];

    return iVLd;
  }
}

//--------------------------------------------------------------------------------
// Read PNG header
//--------------------------------------------------------------------------------
bool QImageMetaData::readPNGHeader(QIODevice& data)
{
  //------------------------------------------------------------------------------
  // Input stream
  //------------------------------------------------------------------------------
  QDataStream* input = new QDataStream(&data);

  //------------------------------------------------------------------------------
  // Endianness
  //------------------------------------------------------------------------------
  input->setByteOrder(QDataStream::BigEndian);

  //------------------------------------------------------------------------------
  // Length
  //------------------------------------------------------------------------------
  quint32 length;

  *input >> length;

  qDebug() << "PNG header length" << length;

  //------------------------------------------------------------------------------
  // Type
  //------------------------------------------------------------------------------
  quint32 type;

  *input >> type;

  PNGType pngType = this->determinePNGType(type);

  if (pngType != IHDR) {
    qDebug() << "Could not find the PNG header.";

    errorMessage_ = QString("Could not find the PNG header.");

    return false;
  }

  //------------------------------------------------------------------------------
  // Width and height
  //------------------------------------------------------------------------------
  quint32 width;
  quint32 height;

  *input >> width;
  *input >> height;

  qDebug() << "PNG width"  << width;
  qDebug() << "PNG height" << height;

  //------------------------------------------------------------------------------
  // Depth
  //------------------------------------------------------------------------------
  quint8 depth;

  *input>> depth;

  qDebug() << "PNG depth" << depth;

  //------------------------------------------------------------------------------
  // Colour type, compression method, filter method, and interlace method
  //------------------------------------------------------------------------------
  quint8 colourType;
  quint8 compressionMethod;
  quint8 filterMethod;
  quint8 interlaceMethod;

  *input >> colourType;
  *input >> compressionMethod;
  *input >> filterMethod;
  *input >> interlaceMethod;

  //------------------------------------------------------------------------------
  // CRC
  //------------------------------------------------------------------------------
  quint32 CRC;

  *input >> CRC;

  //------------------------------------------------------------------------------
  // Sanity checks
  //------------------------------------------------------------------------------
  if (length != 13) {
    errorCode_ = ErrorCodePNGInvalidHeaderLength;

    errorMessage_ = QString("The length of the PNG header is invalid.");

    return false;
  } else if (width == 0) {
    errorCode_ = ErrorCodePNGInvalidHeaderWidth;

    errorMessage_ = QString("The width of the PNG header is invalid.");

    return false;
  } else if (height == 0) {
    errorCode_ = ErrorCodePNGInvalidHeaderHeight;

    errorMessage_ = QString("The height of the PNG header is invalid.");

    return false;
  } else if (depth !=  1 &&
             depth !=  2 &&
             depth !=  4 &&
             depth !=  8 &&
             depth != 16) {
    errorCode_ = ErrorCodePNGInvalidHeaderDepth;

    errorMessage_ = QString("The depth of the PNG header is invalid.");

    return false;
  } else if (colourType != 0 &&
             colourType != 2 &&
             colourType != 3 &&
             colourType != 4 &&
             colourType != 6) {
    errorCode_ = ErrorCodePNGInvalidHeaderColourType;

    errorMessage_ = QString("The colour type of the PNG header is invalid.");

    return false;
  }

  //------------------------------------------------------------------------------
  // Save width, height, and depth
  //------------------------------------------------------------------------------
  width_ = width;

  length_ = height;

  if (colourType == 0) {
    depth_.fill(depth,1);
  } else if (colourType == 2) {
    depth_.fill(depth,3);
  } else if (colourType == 3) {
    depth_.fill(depth,1);
  } else if (colourType == 4) {
    depth_.fill(depth,2);
  } else {
    depth_.fill(depth,4);
  }

  //------------------------------------------------------------------------------
  // Return
  //------------------------------------------------------------------------------
  return true;
}

void QImageMetaData::findPNGTextChunks(QIODevice& data)
{
  //------------------------------------------------------------------------------
  // Input stream
  //------------------------------------------------------------------------------
  QDataStream* input = new QDataStream(&data);

  //------------------------------------------------------------------------------
  // Endianness
  //------------------------------------------------------------------------------
  input->setByteOrder(QDataStream::BigEndian);

  //------------------------------------------------------------------------------
  // Type
  //------------------------------------------------------------------------------
  PNGType pngType = IHDR;

  while (pngType != IEND) {
    //----------------------------------------------------------------------------
    // Length
    //----------------------------------------------------------------------------
    quint32 length;

    *input >> length;

    //----------------------------------------------------------------------------
    // Type
    //----------------------------------------------------------------------------
    quint32 type;

    *input >> type;

    pngType = this->determinePNGType(type);

    //----------------------------------------------------------------------------
    // Save
    //----------------------------------------------------------------------------
    if (pngType == iTXt) {
      iTXtChunks_.append(data.pos() - 8);

      iTXtSizes_.append(length);
    }

    //----------------------------------------------------------------------------
    // Error
    //----------------------------------------------------------------------------
    if (pngType == iVLd) {
      warningCount_++;

      if (warningCount_ > warningLimit_) {
        errorCode_ = ErrorCodeWarningLimitExceeded;

        errorMessage_ = QString("The metadata could not be read, because there were too many warnings.");
      }
    }

    //----------------------------------------------------------------------------
    // Jump
    //----------------------------------------------------------------------------
    data.seek(data.pos() + length + 4);
  }

  qDebug() << "There are" << iTXtChunks_.size() << "iTXt chunks in the PNG data.";
}

void QImageMetaData::readPNGTextChunks(QIODevice& data)
{
  //------------------------------------------------------------------------------
  // Input stream
  //------------------------------------------------------------------------------
  QDataStream* input = new QDataStream(&data);

  //------------------------------------------------------------------------------
  // Endianness
  //------------------------------------------------------------------------------
  input->setByteOrder(QDataStream::BigEndian);

  //------------------------------------------------------------------------------
  // Text chunks
  //------------------------------------------------------------------------------
  for (int i = 0;i < iTXtChunks_.size();++i) {
    data.seek(iTXtChunks_[i] + 8);

    const quint32 keyword_length = 18;

    QString keyword = this->readString(data,keyword_length,data.pos());

    if (keyword.compare("XML:com.adobe.xmp",Qt::CaseSensitive) == 0) {
      qDebug() << "PNG XMP metadata has been found.";

      data.seek(data.pos() + keyword_length);

      quint8 flag;

      *input >> flag;

      quint8 method;

      *input >> method;

      if (flag == 0 && method == 0) {
        data.seek(data.pos() + 2);

        this->displayXMP(data,iTXtSizes_[i] - keyword_length - 4,data.pos());

        QString xmp = this->readString(data,iTXtSizes_[i] - keyword_length - 4,data.pos());

        this->readXMP(xmp);
      }
    }
  }
}

//--------------------------------------------------------------------------------
// JPEG type
//--------------------------------------------------------------------------------
QImageMetaData::JPEGType QImageMetaData::determineJPEGType(quint16 value)
{
  const quint8 first  = (value & 0xFF00) >> 8;

  const quint8 second = (value & 0x00FF);

  if (first == 0xFF) {
    if (second == 0xD8) {
      return SOI;
    } else if (second == 0xC0) {
      return SOF0;
    } else if (second == 0xC1) {
      return SOF1;
    } else if (second == 0xC2) {
      return SOF2;
    } else if (second == 0xC3) {
      return SOF3;
    } else if (second == 0xC5) {
      return SOF5;
    } else if (second == 0xC6) {
      return SOF6;
    } else if (second == 0xC7) {
      return SOF7;
    } else if (second == 0xC8) {
      return JPG;
    } else if (second == 0xC9) {
      return SOF9;
    } else if (second == 0xCA) {
      return SOF10;
    } else if (second == 0xCB) {
      return SOF11;
    } else if (second == 0xCD) {
      return SOF13;
    } else if (second == 0xCE) {
      return SOF14;
    } else if (second == 0xCF) {
      return SOF15;
    } else if (second == 0xC4) {
      return DHT;
    } else if (second == 0xCC) {
      return DAC;
    } else if (second == 0xDB) {
      return DQT;
    } else if (second == 0xDC) {
      return DNL;
    } else if (second == 0xDD) {
      return DRI;
    } else if (second == 0xDE) {
      return DHP;
    } else if (second == 0xDF) {
      return EXP;
    } else if (second == 0xDA) {
      return SOS;
    } else if (second == 0xD0) {
      return RST0;
    } else if (second == 0xD1) {
      return RST1;
    } else if (second == 0xD2) {
      return RST2;
    } else if (second == 0xD3) {
      return RST3;
    } else if (second == 0xD4) {
      return RST4;
    } else if (second == 0xD5) {
      return RST5;
    } else if (second == 0xD6) {
      return RST6;
    } else if (second == 0xC7) {
      return RST7;
    } else if (second == 0xE0) {
      return APP0;
    } else if (second == 0xE1) {
      return APP1;
    } else if (second == 0xE2) {
      return APP2;
    } else if (second == 0xE3) {
      return APP3;
    } else if (second == 0xE4) {
      return APP4;
    } else if (second == 0xE5) {
      return APP5;
    } else if (second == 0xE6) {
      return APP6;
    } else if (second == 0xE7) {
      return APP7;
    } else if (second == 0xE8) {
      return APP8;
    } else if (second == 0xE9) {
      return APP9;
    } else if (second == 0xEA) {
      return APPA;
    } else if (second == 0xEB) {
      return APPB;
    } else if (second == 0xEC) {
      return APPC;
    } else if (second == 0xED) {
      return APPD;
    } else if (second == 0xEE) {
      return APPE;
    } else if (second == 0xEF) {
      return APPF;
    } else if (second == 0xF0) {
      return JPG0;
    } else if (second == 0xF1) {
      return JPG1;
    } else if (second == 0xF2) {
      return JPG2;
    } else if (second == 0xF3) {
      return JPG3;
    } else if (second == 0xF4) {
      return JPG4;
    } else if (second == 0xF5) {
      return JPG5;
    } else if (second == 0xF6) {
      return JPG6;
    } else if (second == 0xF7) {
      return JPG7;
    } else if (second == 0xF8) {
      return JPG8;
    } else if (second == 0xF9) {
      return JPG9;
    } else if (second == 0xFA) {
      return JPGA;
    } else if (second == 0xFB) {
      return JPGB;
    } else if (second == 0xFC) {
      return JPGC;
    } else if (second == 0xFD) {
      return JPGD;
    } else if (second == 0xFE) {
      return JPGE;
    } else if (second == 0xFF) {
      return JPGF;
    } else if (second == 0xFE) {
      return COM;
    } else if (second == 0x01) {
      return TEM;
    } else if (second == 0xD9) {
      return EOI;
    } else {
      return IVL;
    }
  } else {
    return IVL;
  }
}

//--------------------------------------------------------------------------------
// Identify
//--------------------------------------------------------------------------------
bool QImageMetaData::identify(QIODevice& data)
{
  //------------------------------------------------------------------------------
  // Image format
  //------------------------------------------------------------------------------
  imageFormat_ = ImageFormatUndefined;

  //------------------------------------------------------------------------------
  // Input stream
  //------------------------------------------------------------------------------
  QDataStream* input = new QDataStream(&data);

  //------------------------------------------------------------------------------
  // Start
  //------------------------------------------------------------------------------
  quint16 n;

  *input >> n;

  //------------------------------------------------------------------------------
  // JPEG
  //------------------------------------------------------------------------------
  if (n == 0xFFD8) {
    //----------------------------------------------------------------------------
    // Image format
    //----------------------------------------------------------------------------
    imageFormat_ = ImageFormatJPEG;

    //----------------------------------------------------------------------------
    // Find the EXIF information
    //----------------------------------------------------------------------------
    quint16 marker;
    quint16 length;

    while (true) {
      //--------------------------------------------------------------------------
      // Marker and length
      //--------------------------------------------------------------------------
      *input >> marker;

      *input >> length;

      //--------------------------------------------------------------------------
      // Marker type
      //--------------------------------------------------------------------------
      JPEGType type = this->determineJPEGType(marker);

      //--------------------------------------------------------------------------
      // APP1
      //--------------------------------------------------------------------------
      if (type == APP1) {
        //------------------------------------------------------------------------
        // EXIF
        //------------------------------------------------------------------------
        if (length != 0) {
          quint32 exif;

          *input >> exif;

          if (exif == 0x45786966) {
            *input >> n;

            break;
          } else {
            data.seek(data.pos() + static_cast<qint64>(length) - 2 - 4);
          }
        }

      //--------------------------------------------------------------------------
      // EOI
      //--------------------------------------------------------------------------
      } else if (type == EOI) {
        break;

      //--------------------------------------------------------------------------
      // RST
      //--------------------------------------------------------------------------
      } else if (type == RST0 ||
                 type == RST1 ||
                 type == RST2 ||
                 type == RST3 ||
                 type == RST4 ||
                 type == RST5 ||
                 type == RST6 ||
                 type == RST7) {
        data.seek(data.pos() - 2);

        break;

      //--------------------------------------------------------------------------
      // TEM
      //--------------------------------------------------------------------------
      } else if (type == TEM) {
        data.seek(data.pos() - 2);

        break;

      //--------------------------------------------------------------------------
      // IVL
      //--------------------------------------------------------------------------
      } else if (type == IVL) {
        warningCount_++;

        if (warningCount_ > warningLimit_) {
          errorCode_ = ErrorCodeWarningLimitExceeded;

          errorMessage_ = QString("The metadata could not be read, because there were too many warnings.");

          break;
        }

      //--------------------------------------------------------------------------
      // Other
      //--------------------------------------------------------------------------
      } else {
        data.seek(data.pos() + static_cast<qint64>(length) - 2);
      }
    }
  }

  //------------------------------------------------------------------------------
  // Header
  //------------------------------------------------------------------------------
  if (imageFormat_ == ImageFormatJPEG) {
    baseOffset_ = data.pos();

    *input >> n;
  }

  //------------------------------------------------------------------------------
  // TIFF
  //------------------------------------------------------------------------------
  if (n == 0x4949 || n == 0x4D4D) {
    //----------------------------------------------------------------------------
    // Endianness
    //----------------------------------------------------------------------------
    if (n == 0x4949) {
      endianness_ = QDataStream::LittleEndian;

      input->setByteOrder(endianness_);
    } else {
      endianness_ = QDataStream::BigEndian;

      input->setByteOrder(endianness_);
    }

    //----------------------------------------------------------------------------
    // Identification number
    //----------------------------------------------------------------------------
    *input >> n;

    if (n != 42) {
      imageFormat_ = ImageFormatUnknown;
    } else if (imageFormat_ == ImageFormatUndefined) {
      imageFormat_ = ImageFormatTIFF;
    }

    //----------------------------------------------------------------------------
    // Offset to the first IFD
    //----------------------------------------------------------------------------
    tiffValid_ = true;

    *input >> tiffOffset_;

    tiffOffset_ = data.pos() - 8 + tiffOffset_;

    //----------------------------------------------------------------------------
    // Return
    //----------------------------------------------------------------------------
    return true;
  }

  //------------------------------------------------------------------------------
  // PNG
  //------------------------------------------------------------------------------
  if (imageFormat_ == ImageFormatUndefined || imageFormat_ == ImageFormatUnknown) {
    imageFormat_ = ImageFormatPNG;

    data.seek(0);

    const int pngHeaderLength = 8;

    for (int i = 0;i < pngHeaderLength;++i) {
      quint8 m;

      *input >> m;

      if ((i == 0 && m != 0x89) ||
          (i == 1 && m != 0x50) ||
          (i == 2 && m != 0x4E) ||
          (i == 3 && m != 0x47) ||
          (i == 4 && m != 0x0D) ||
          (i == 5 && m != 0x0A) ||
          (i == 6 && m != 0x1A) ||
          (i == 7 && m != 0x0A)) {
        imageFormat_ = ImageFormatUnknown;

        break;
      }
    }

    if (this->readPNGHeader(data)) {
      return true;
    } else {
      return false;
    }
  }

  //------------------------------------------------------------------------------
  // Return
  //------------------------------------------------------------------------------
  errorCode_ = ErrorCodeImageFormatNotIdentified;

  errorMessage_ = QString("Could not identify the image format.");

  return false;
}

//--------------------------------------------------------------------------------
// Byte Count
//--------------------------------------------------------------------------------
quint32 QImageMetaData::byteCount(quint16 type,quint32 count)
{
  if (type == 1) {
    return count;

  } else if (type == 3) {
    return 2*count;

  } else if (type == 4) {
    return 4*count;

  } else {
    return 0;
  }
}

//--------------------------------------------------------------------------------
// Left justified
//--------------------------------------------------------------------------------
bool QImageMetaData::leftJustified(quint16 type,quint32 count)
{
  if (type == 1) {
    if (count < 4) {
      return true;
    } else {
      return false;
    }
  } else if (type == 3) {
    if (count < 2) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

//--------------------------------------------------------------------------------
// Justify
//--------------------------------------------------------------------------------
quint32 QImageMetaData::justify(QIODevice& data,quint32 type)
{
  //------------------------------------------------------------------------------
  // Input stream
  //------------------------------------------------------------------------------
  QDataStream* input = new QDataStream(&data);

  input->setByteOrder(endianness_);

  //------------------------------------------------------------------------------
  // Justify
  //------------------------------------------------------------------------------
  quint8  tmp8;
  quint16 tmp16;

  quint32 value;

  if (type == 1) {
    *input >> tmp8;

    value = tmp8;

    data.seek(data.pos() + 3);
  } else {
    *input >> tmp16;

    value = tmp16;

    data.seek(data.pos() + 2);
  }

  //------------------------------------------------------------------------------
  // Value
  //------------------------------------------------------------------------------
  return value;
}

//--------------------------------------------------------------------------------
// Read string (XML)
//--------------------------------------------------------------------------------
bool QImageMetaData::readXMPEntry(QXmlStreamReader &xml,QString name,QString &text)
{
  bool success = true;

  QXmlStreamReader::TokenType token = xml.readNext();

  if (token == QXmlStreamReader::Characters) {
    text = xml.text().toString();

    token = xml.readNext();

    if (token != QXmlStreamReader::EndElement || name.compare(xml.name().toString()) != 0) {
      success = false;
    }
  } else {
    success = false;
  }

  return success;
}

void QImageMetaData::readXMPString(QXmlStreamReader &xml,QString name,QString &entry)
{
  QString text;

  if (this->readXMPEntry(xml,name,text)) {
    entry = text;

    debugXMPText_ = text;
  }
}

void QImageMetaData::readXMPString(QXmlStreamReader &xml,QString name,quint32 &entry)
{
  QString text;

  if (this->readXMPEntry(xml,name,text)) {
    entry = this->convertToUint(length_,text);

    debugXMPText_ = text;
  }
}

void QImageMetaData::readXMPStringArray(QXmlStreamReader &xml,QString name,QVector<quint32> &entry)
{
  QVector<QString> text;

  if (this->readXMPStringArray(xml,text,name)) {
    entry = this->convertToUint(entry,text);

    debugXMPText_ = "";

    for (int i = 0;i < text.size();++i) {
      debugXMPText_ += text[i];

      if (i < text.size() - 1)
        debugXMPText_ += ",";
    }
  }
}

bool QImageMetaData::readXMPType(QXmlStreamReader &xml,QString name,QString &entry)
{
  QString text;

  if (this->readXMPEntry(xml,name,text)) {
    entry = text;

    debugXMPText_ = text;

    return true;
  } else {
    return false;
  }
}

bool QImageMetaData::readXMPType(QXmlStreamReader &xml,QString name,quint32 &entry)
{
  QString text;

  if (this->readXMPEntry(xml,name,text)) {
    debugXMPText_ = text;

    if (this->convertToUint(text,entry)) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

void QImageMetaData::readXMPRationalUnsigned(QXmlStreamReader &xml,QString name,QImageMetaDataRational<quint32> &rational)
{
  QString text;

  if (this->readXMPEntry(xml,name,text)) {
    this->setUnsignedRational(text,rational);

    debugXMPText_ = text;
  }
}

void QImageMetaData::readXMPRationalUnsignedArray(QXmlStreamReader &xml,QString name,QVector< QImageMetaDataRational<quint32> > &rational)
{
  QVector<QString> text;

  if (this->readXMPStringArray(xml,text,name))
    this->setUnsignedRational(text,rational);

  debugXMPText_ = "";

  for (int i = 0;i < text.size();++i) {
    debugXMPText_ += text[i];

    if (i < text.size() - 1)
      debugXMPText_ += ",";
  }
}

void QImageMetaData::readXMPRationalSigned(QXmlStreamReader &xml,QString name,QImageMetaDataRational<qint32> &rational)
{
  QString text;

  if (this->readXMPEntry(xml,name,text)) {
    this->setSignedRational(text,rational);

    debugXMPText_ = text;
  }
}

//--------------------------------------------------------------------------------
// Read string array (XML)
//--------------------------------------------------------------------------------
bool QImageMetaData::readXMPStringArray(QXmlStreamReader &xml,QVector<QString> &text,QString name)
{
  bool success = true;

  text.clear();

  QXmlStreamReader::TokenType token = xml.readNext();

  while (!xml.atEnd() && !xml.hasError()) {
    if (token == QXmlStreamReader::StartElement && xml.name().toString().compare("seq",Qt::CaseInsensitive) == 0) {

    } else if (token == QXmlStreamReader::EndElement && xml.name().toString().compare("seq",Qt::CaseInsensitive) == 0) {
      break;

    } else if (token == QXmlStreamReader::StartElement) {
      token = xml.readNext();

      if (token == QXmlStreamReader::Characters) {
        text.append(xml.text().toString());

        token = xml.readNext();

        if (token != QXmlStreamReader::EndElement) {
          success = false;

          break;
        }
      } else {
        success = false;

        break;
      }

    } else if (token != QXmlStreamReader::EndElement && name.compare(xml.name().toString()) == 0) {
      break;
    }

    token = xml.readNext();
  }

  return success;
}

//--------------------------------------------------------------------------------
// Auxiliary conversion function
//--------------------------------------------------------------------------------
quint32 QImageMetaData::convertToUint(quint32 value,QString text)
{
  bool conversion;

  quint32 result = text.toUInt(&conversion);

  if (!conversion)
    result = value;

  return result;
}

bool QImageMetaData::convertToUint(QString text,quint32 &value)
{
  bool conversion;

  quint32 result = text.toUInt(&conversion);

  if (conversion)
    value = result;

  return conversion;
}

//--------------------------------------------------------------------------------
// Auxiliary conversion function
//--------------------------------------------------------------------------------
QVector<quint32> QImageMetaData::convertToUint(QVector<quint32> value,QVector<QString> text)
{
  bool conversion;

  QVector<quint32> result;

  for (int i = 0;i < text.size();++i) {
    result.append(text[0].toUInt(&conversion));

    if (!conversion) {
      result = value;

      break;
    }
  }

  return result;
}

bool QImageMetaData::compareName(QString keyword,QString name)
{
  if (name.compare(keyword,Qt::CaseInsensitive) == 0) {
    return true;
  } else {
    return false;
  }
}

void QImageMetaData::setUnsignedRational(QString text,QImageMetaDataRational<quint32> &rational)
{
  QStringList list = text.split("/");

  if (list.size() == 2) {
    const QString nomString = list[0];
    const QString denString = list[1];

    bool nomStatus;
    bool denStatus;

    const quint32 nomValue = nomString.toUInt(&nomStatus);
    const quint32 denValue = denString.toUInt(&denStatus);

    if (nomStatus && denStatus) {
      rational.setNominator(nomValue);
      rational.setDenominator(denValue);
    }
  } else {
    const QString valString = list[0];

    bool nbrStatus;

    const quint32 nbrValue = valString.toUInt(&nbrStatus);

    if (nbrStatus) {
      rational.setNominator(nbrValue);
      rational.setDenominator(1);
    }
  }
}

QVector<  QImageMetaDataRational<quint32> > QImageMetaData::setUnsignedRational(QVector<QString> text,QVector< QImageMetaDataRational<quint32> > &rationalArray)
{
  QVector< QImageMetaDataRational<quint32> > result;

  for (int i = 0;i < text.size();++i) {
    QStringList list = text[i].split("/");

    QImageMetaDataRational<quint32> rational;

    const QString nomString = list[0];
    const QString denString = list[1];

    bool nomStatus;
    bool denStatus;

    if (list.size() == 2) {
      const quint32 nomValue = nomString.toUInt(&nomStatus);
      const quint32 denValue = denString.toUInt(&denStatus);

      if (nomStatus == true && denStatus == true) {
        rational.setNominator(nomValue);
        rational.setDenominator(denValue);

        result.append(rational);
      } else {
        result = rationalArray;

        break;
      }
    }
  }

  return result;
}

void QImageMetaData::setSignedRational(QString text,QImageMetaDataRational<qint32> &rational)
{
  QStringList list = text.split("/");

  if (list.size() == 2) {
    const QString nomString = list[0];
    const QString denString = list[1];

    bool nomStatus;
    bool denStatus;

    const qint32 nomValue = nomString.toInt(&nomStatus);
    const qint32 denValue = denString.toInt(&denStatus);

    if (nomStatus && denStatus) {
      rational.setNominator(nomValue);
      rational.setDenominator(denValue);
    }
  } else {
    const QString valString = list[0];

    bool nbrStatus;

    const qint32 nbrValue = valString.toInt(&nbrStatus);

    if (nbrStatus) {
      rational.setNominator(nbrValue);
      rational.setDenominator(1);
    }
  }
}

//--------------------------------------------------------------------------------
// Define tag number
//--------------------------------------------------------------------------------
unsigned int QImageMetaData::defineTag(QString name)
{
  //------------------------------------------------------------------------------
  // Tag
  //------------------------------------------------------------------------------
  unsigned int tag = 0;

  //------------------------------------------------------------------------------
  // Map
  //------------------------------------------------------------------------------
  QMap<QString,unsigned int> map;

  //------------------------------------------------------------------------------
  // TIFF entries
  //------------------------------------------------------------------------------
  map.insert("artist",QIMAGEMETADATA_ARTIST);
  map.insert("bitspersample",QIMAGEMETADATA_BITSPERSAMPLE);
  map.insert("compression",QIMAGEMETADATA_COMPRESSION);
  map.insert("copyright",QIMAGEMETADATA_COPYRIGHT);
  map.insert("datetime",QIMAGEMETADATA_DATETIME);
  map.insert("imagedescription",QIMAGEMETADATA_IMAGEDESCRIPTION);
  map.insert("imagewidth",QIMAGEMETADATA_IMAGEWIDTH);
  map.insert("imagelength",QIMAGEMETADATA_IMAGELENGTH);
  map.insert("make",QIMAGEMETADATA_MAKE);
  map.insert("model",QIMAGEMETADATA_MODEL);
  map.insert("orientation",QIMAGEMETADATA_ORIENTATION);
  map.insert("photometricinterpretation",QIMAGEMETADATA_PHOTOMETRICINTERPRETATION);
  map.insert("planarconfiguration",QIMAGEMETADATA_PLANARCONFIGURATION);
  map.insert("primarychromaticities",QIMAGEMETADATA_PRIMARYCHROMATICITIES);
  map.insert("referenceblackWhite",QIMAGEMETADATA_REFERENCEBLACKWHITE);
  map.insert("resolutionunit",QIMAGEMETADATA_RESOLUTIONUNIT);
  map.insert("samplesperpixel",QIMAGEMETADATA_SAMPLESPERPIXEL);
  map.insert("software",QIMAGEMETADATA_SOFTWARE);
  map.insert("transferfunction",QIMAGEMETADATA_TRANSFERFUNCTION);
  map.insert("whitepoint",QIMAGEMETADATA_WHITEPOINT);
  map.insert("xresolution",QIMAGEMETADATA_XRESOLUTION);
  map.insert("yresolution",QIMAGEMETADATA_YRESOLUTION);
  map.insert("ycbcrcoefficients",QIMAGEMETADATA_YCBCRCOEFFICIENTS);
  map.insert("ycbcrpositioning",QIMAGEMETADATA_YCBCRPOSITIONING);
  map.insert("ycbcrsubsampling",QIMAGEMETADATA_YCBCRSUBSAMPLING);

  //------------------------------------------------------------------------------
  // EXIF entries
  //------------------------------------------------------------------------------
  map.insert("aperturevalue",QIMAGEMETADATA_APERTUREVALUE);
  map.insert("brightness",QIMAGEMETADATA_BRIGHTNESSVALUE);
  map.insert("colorspace",QIMAGEMETADATA_COLORSPACE);
  map.insert("componentsconfiguration",QIMAGEMETADATA_COMPONENTSCONFIGURATION);
  map.insert("compressedbitsperpixel",QIMAGEMETADATA_COMPRESSEDBITSPERPIXEL);
  map.insert("contrast",QIMAGEMETADATA_CONTRAST);
  map.insert("customrendered",QIMAGEMETADATA_CUSTOMRENDERED);
  map.insert("datetimeoriginal",QIMAGEMETADATA_DATETIMEORIGINAL);
  map.insert("datetimedigitized",QIMAGEMETADATA_DATETIMEDIGITIZED);
  map.insert("digitalzoomratio",QIMAGEMETADATA_DIGITALZOOMRATIO);
  map.insert("exifversion",QIMAGEMETADATA_EXIFVERSION);
  map.insert("exposurebiasvalue",QIMAGEMETADATA_EXPOSUREBIASVALUE);
  map.insert("exposureindex",QIMAGEMETADATA_EXPOSUREINDEX);
  map.insert("exposuremode",QIMAGEMETADATA_EXPOSUREMODE);
  map.insert("exposureprogram",QIMAGEMETADATA_EXPOSUREPROGRAM);
  map.insert("exposuretime",QIMAGEMETADATA_EXPOSURETIME);
  map.insert("flash",QIMAGEMETADATA_FLASH);
  map.insert("flashenergy",QIMAGEMETADATA_FLASHENERGY);
  map.insert("flashpixversion",QIMAGEMETADATA_FLASHPIXVERSION);
  map.insert("fnumber",QIMAGEMETADATA_FNUMBER);
  map.insert("focallength",QIMAGEMETADATA_FOCALLENGTH);
  map.insert("focallengthin35mmfilm",QIMAGEMETADATA_FOCALLENGTHIN35MMFILM);
  map.insert("focalplaneresolutionunit",QIMAGEMETADATA_FOCALPLANERESOLUTIONUNIT);
  map.insert("focalplanexresolution",QIMAGEMETADATA_FOCALPLANEXRESOLUTION);
  map.insert("focalplaneyresolution",QIMAGEMETADATA_FOCALPLANEYRESOLUTION);
  map.insert("gaincontrol",QIMAGEMETADATA_GAINCONTROL);
  map.insert("imageuniqueid",QIMAGEMETADATA_IMAGEUNIQUEID);
  map.insert("isospeedratings",QIMAGEMETADATA_ISOSPEEDRATINGS);
  map.insert("lightsource",QIMAGEMETADATA_LIGHTSOURCE);
  map.insert("maxaperturevalue",QIMAGEMETADATA_MAXAPERTUREVALUE);
  map.insert("meteringmode",QIMAGEMETADATA_METERINGMODE);
  map.insert("pixelxdimension",QIMAGEMETADATA_PIXELXDIMENSION);
  map.insert("pixelydimension",QIMAGEMETADATA_PIXELYDIMENSION);
  map.insert("relatedsoundfile",QIMAGEMETADATA_RELATEDSOUNDFILE);
  map.insert("saturation",QIMAGEMETADATA_SATURATION);
  map.insert("scenecapturetype",QIMAGEMETADATA_SCENECAPTURETYPE);
  map.insert("sensingmethod",QIMAGEMETADATA_SENSINGMETHOD);
  map.insert("sharpness",QIMAGEMETADATA_SHARPNESS);
  map.insert("shutterspeedvalue",QIMAGEMETADATA_SHUTTERSPEEDVALUE);
  map.insert("spectralsensitivity",QIMAGEMETADATA_SPECTRALSENSITIVITY);
  map.insert("subjectdistance",QIMAGEMETADATA_SUBJECTDISTANCE);
  map.insert("subjectdistanceRange",QIMAGEMETADATA_SUBJECTDISTANCERANGE);
  map.insert("subjectlocation",QIMAGEMETADATA_SUBJECTLOCATION);
  map.insert("whitebalance",QIMAGEMETADATA_WHITEBALANCE);

  //------------------------------------------------------------------------------
  // GPS entries
  //------------------------------------------------------------------------------
  map.insert("gpsaltitude",QIMAGEMETADATA_GPSALTITUDE);
  map.insert("gpsaltitudeRef",QIMAGEMETADATA_GPSALTITUDEREF);
  map.insert("gpsdestBearing",QIMAGEMETADATA_GPSDESTBEARING);
  map.insert("gpsdestBearingRef",QIMAGEMETADATA_GPSDESTBEARINGREF);
  map.insert("gpsdestDistance",QIMAGEMETADATA_GPSDESTDISTANCE);
  map.insert("gpsdestDistanceRef",QIMAGEMETADATA_GPSDESTDISTANCEREF);
  map.insert("gpsdestLatitude",QIMAGEMETADATA_GPSDESTLATITUDE);
  map.insert("gpsdestLongitude",QIMAGEMETADATA_GPSDESTLONGITUDE);
  map.insert("gpsdifferential",QIMAGEMETADATA_GPSDIFFERENTIAL);
  map.insert("gpsdop",QIMAGEMETADATA_GPSDOP);
  map.insert("gpsimgdirection",QIMAGEMETADATA_GPSIMGDIRECTION);
  map.insert("gpsimgdirectionRef",QIMAGEMETADATA_GPSIMGDIRECTIONREF);
  map.insert("gpslatituderef",QIMAGEMETADATA_GPSLATITUDEREF);
  map.insert("gpslatitude",QIMAGEMETADATA_GPSLATITUDE);
  map.insert("gpslongituderef",QIMAGEMETADATA_GPSLONGITUDEREF);
  map.insert("gpslongitude",QIMAGEMETADATA_GPSLONGITUDE);
  map.insert("gpsmapdatum",QIMAGEMETADATA_GPSMAPDATUM);
  map.insert("gpsmeasuremode",QIMAGEMETADATA_GPSMEASUREMODE);
  map.insert("gpssatellites",QIMAGEMETADATA_GPSSATELLITES);
  map.insert("gpsspeed",QIMAGEMETADATA_GPSSPEED);
  map.insert("gpsspeedref",QIMAGEMETADATA_GPSSPEEDREF);
  map.insert("gpsstatus",QIMAGEMETADATA_GPSSTATUS);
  map.insert("gpstimestamp",QIMAGEMETADATA_GPSTIMESTAMP);
  map.insert("gpstrack",QIMAGEMETADATA_GPSTRACK);
  map.insert("gpstrackref",QIMAGEMETADATA_GPSTRACKREF);

  //------------------------------------------------------------------------------
  // XMP
  //------------------------------------------------------------------------------
  map.insert("lens",QIMAGEMETADATA_LENS);
  map.insert("serialnumber",QIMAGEMETADATA_SERIALNUMBER);

  //------------------------------------------------------------------------------
  // Tag
  //------------------------------------------------------------------------------
  if (map.contains(name.toLower())) {
    tag = map.value(name.toLower());
  }

  //------------------------------------------------------------------------------
  // Return
  //------------------------------------------------------------------------------
  return tag;
}

QVector<  QImageMetaDataRational<qint32> > QImageMetaData::setSignedRational(QVector<QString> text,QVector< QImageMetaDataRational<qint32> > &rationalArray)
{
  QVector< QImageMetaDataRational<qint32> > result;

  for (int i = 0;i < text.size();++i) {
    QStringList list = text[i].split("/");

    QImageMetaDataRational<qint32> rational;

    const QString nomString = list[0];
    const QString denString = list[1];

    bool nomStatus;
    bool denStatus;

    if (list.size() == 2) {
      const qint32 nomValue = nomString.toInt(&nomStatus);
      const qint32 denValue = denString.toInt(&denStatus);

      if (nomStatus == true && denStatus == true) {
        rational.setNominator(nomValue);
        rational.setDenominator(denValue);

        result.append(rational);
      } else {
        result = rationalArray;

        break;
      }
    }
  }

  return result;
}

//--------------------------------------------------------------------------------
// Read XMP
//--------------------------------------------------------------------------------
void QImageMetaData::readXMP(QString xmp)
{
  //------------------------------------------------------------------------------
  // XML reader
  //------------------------------------------------------------------------------
  QXmlStreamReader xml(xmp);

  if (xml.documentEncoding().toString().compare("") == 0) {
    qDebug() << "XML encoding has not been defined.";
  } else {
    qDebug() << "XML encoding " << xml.documentEncoding().toString() << "has been enabled.";
  }

  QString name;
  QString text;

  QVector<QString> textArray;

  quint32 value;

  //------------------------------------------------------------------------------
  // Main loop
  //------------------------------------------------------------------------------
  while (!xml.atEnd() && !xml.hasError()) {
    QXmlStreamReader::TokenType token = xml.readNext();

    if (token == QXmlStreamReader::StartDocument) {

    } else if (token == QXmlStreamReader::EndDocument) {
      break;

    } else if (token == QXmlStreamReader::StartElement && xml.name().toString().compare("xmpmeta") == 0) {
      qDebug() << "XMP metadata start element has been found.";

    } else if (token == QXmlStreamReader::EndElement && xml.name().toString().compare("xmpmeta") == 0) {
      qDebug() << "XMP metadata end element has been found.";

      break;

    } else if (token == QXmlStreamReader::StartElement) {
      name = xml.name().toString();

      debugXMPName_ = name;

      const unsigned int tag = this->defineTag(name);

      switch (tag) {
      //--------------------------------------------------------------------------
      // TIFF entries
      //--------------------------------------------------------------------------
      case QIMAGEMETADATA_ARTIST: {
          this->readXMPString(xml,name,artist_);
          break;
        }

      case QIMAGEMETADATA_BITSPERSAMPLE: {
          this->readXMPStringArray(xml,name,depth_);
          break;
        }

      case QIMAGEMETADATA_COMPRESSION: {
          if (this->readXMPType(xml,name,value)) {
            compression_ = this->compressionType(value);
          }
          break;
        }

      case QIMAGEMETADATA_COPYRIGHT: {
          this->readXMPString(xml,name,copyright_);
          break;
        }

      case QIMAGEMETADATA_DATETIME: {
          this->readXMPString(xml,name,dateAndTime_);
          break;
        }

      case QIMAGEMETADATA_IMAGEDESCRIPTION: {
          this->readXMPString(xml,name,imageDescription_);
          break;
        }

      case QIMAGEMETADATA_IMAGELENGTH: {
          this->readXMPString(xml,name,length_);
          break;
        }

      case QIMAGEMETADATA_IMAGEWIDTH: {
          this->readXMPString(xml,name,width_);
          break;
        }

      case QIMAGEMETADATA_MAKE: {
          this->readXMPString(xml,name,make_);
          break;
        }

      case QIMAGEMETADATA_MODEL: {
          this->readXMPString(xml,name,model_);
          break;
        }

      case QIMAGEMETADATA_ORIENTATION: {
          if (this->readXMPType(xml,name,value)) {
            orientation_ = this->orientationType(value);
          }
          break;
        }

      case QIMAGEMETADATA_PHOTOMETRICINTERPRETATION: {
          if (this->readXMPType(xml,name,value)) {
            photometric_ = this->photometricInterpretationType(value);
          }
          break;
        }

      case QIMAGEMETADATA_PLANARCONFIGURATION: {
          if (this->readXMPType(xml,name,value)) {
            planar_ = this->planarConfigurationType(value);
          }
          break;
        }

      case QIMAGEMETADATA_PRIMARYCHROMATICITIES: {
          this->readXMPRationalUnsignedArray(xml,name,primaryChromaticities_);
          break;
        }

      case QIMAGEMETADATA_REFERENCEBLACKWHITE: {
          this->readXMPRationalUnsignedArray(xml,name,referenceBlackWhite_);
          break;
        }

      case QIMAGEMETADATA_RESOLUTIONUNIT: {
          if (this->readXMPType(xml,name,value)) {
            resolution_ = this->resolutionUnitType(value);
          }
          break;
        }

      case QIMAGEMETADATA_SAMPLESPERPIXEL: {
          this->readXMPString(xml,name,samples_);
          break;
        }

      case QIMAGEMETADATA_SOFTWARE: {
          this->readXMPString(xml,name,software_);
          break;
        }

      case QIMAGEMETADATA_TRANSFERFUNCTION: {
          this->readXMPStringArray(xml,name,transferFunction_);
          break;
        }

      case QIMAGEMETADATA_WHITEPOINT: {
          this->readXMPRationalUnsignedArray(xml,name,whitePoint_);
          break;
        }

      case QIMAGEMETADATA_XRESOLUTION: {
          this->readXMPRationalUnsigned(xml,name,xResolution_);
          break;
        }

      case QIMAGEMETADATA_YRESOLUTION: {
          this->readXMPRationalUnsigned(xml,name,yResolution_);
          break;
        }

      case QIMAGEMETADATA_YCBCRCOEFFICIENTS: {
          this->readXMPRationalUnsignedArray(xml,name,yCbCrCoefficients_);
          break;
        }

      case QIMAGEMETADATA_YCBCRPOSITIONING: {
          if (this->readXMPType(xml,name,value)) {
            yCbCrPositioning_ = this->yCbCrPositioningType(value);
          }
          break;
        }

      case QIMAGEMETADATA_YCBCRSUBSAMPLING: {
          this->readXMPStringArray(xml,name,yCbCrSubSampling_);
          break;
        }

      //--------------------------------------------------------------------------
      // EXIF entries
      //--------------------------------------------------------------------------
      default: {

        }
      }

      //--------------------------------------------------------------------------
      // EXIF entries
      //--------------------------------------------------------------------------
      if (this->compareName("ApertureValue",name)) {
        this->readXMPRationalUnsigned(xml,name,aperture_);

      } else if (this->compareName("Brightness",name)) {
        this->readXMPRationalSigned(xml,name,brightness_);

      } else if (this->compareName("ColorSpace",name)) {
        if (this->readXMPType(xml,name,value)) {
          colorSpace_ = this->colorSpaceType(value);
        }

      } else if (this->compareName("ComponentsConfiguration",name)) {
        this->readXMPStringArray(xml,name,componentsConfiguration_);

      } else if (this->compareName("CompressedBitsPerPixel",name)) {
        this->readXMPRationalUnsigned(xml,name,compressedBitsPerPixel_);

      } else if (this->compareName("Contrast",name)) {
        if (this->readXMPType(xml,name,value)) {
          contrast_ = this->contrastType(value);
        }

      } else if (this->compareName("CustomRendered",name)) {
        if (this->readXMPType(xml,name,value)) {
          customRendered_ = this->customRenderedType(value);
        }

      } else if (this->compareName("DateTimeOriginal",name)) {
        this->readXMPString(xml,name,dateAndTimeOriginal_);

      } else if (this->compareName("DateTimeDigitized",name)) {
        this->readXMPString(xml,name,dateAndTimeDigitized_);

      } else if (this->compareName("DigitalZoomRatio",name)) {
        this->readXMPRationalUnsigned(xml,name,digitalZoomRatio_);

      } else if (this->compareName("ExifVersion",name)) {
        this->readXMPString(xml,name,exifVersion_);

      } else if (this->compareName("ExposureBiasValue",name)) {
        this->readXMPRationalSigned(xml,name,exposureBias_);

      } else if (this->compareName("ExposureIndex",name)) {
        this->readXMPRationalUnsigned(xml,name,exposureIndex_);

      } else if (this->compareName("ExposureMode",name)) {
        if (this->readXMPType(xml,name,value)) {
          exposureMode_ = this->exposureModeType(value);
        }

      } else if (this->compareName("ExposureProgram",name)) {
        if (this->readXMPType(xml,name,value)) {
          exposureProgram_ = this->exposureProgramType(value);
        }

      } else if (this->compareName("ExposureTime",name)) {
        this->readXMPRationalUnsigned(xml,name,exposureTime_);

      } else if (this->compareName("Flash",name)) {
        this->readXMPString(xml,name,flash_);

        flashStatus_   = this->flashStatusType();
        flashStrobe_   = this->flashStrobeType();
        flashMode_     = this->flashModeType();
        flashFunction_ = this->flashFunctionType();
        flashRedEye_   = this->flashRedEeyeType();

      } else if (this->compareName("FlashEnergy",name)) {
        this->readXMPRationalUnsigned(xml,name,flashEnergy_);

      } else if (this->compareName("FlashPixVersion",name)) {
        this->readXMPString(xml,name,flashPixVersion_);

      } else if (this->compareName("FNumber",name)) {
        this->readXMPRationalUnsigned(xml,name,fNumber_);

      } else if (this->compareName("FocalLength",name)) {
        this->readXMPRationalUnsigned(xml,name,focalLength_);

      } else if (this->compareName("FocalLengthIn35mmFilm",name)) {
        this->readXMPString(xml,name,focalLength35mm_);

      } else if (this->compareName("FocalPlaneResolutionUnit",name)) {
        if (this->readXMPType(xml,name,value)) {
          focalPlaneResolution_ = this->resolutionUnitType(value);
        }

      } else if (this->compareName("FocalPlaneXResolution",name)) {
        this->readXMPRationalUnsigned(xml,name,focalPlaneXResolution_);

      } else if (this->compareName("FocalPlaneYResolution",name)) {
        this->readXMPRationalUnsigned(xml,name,focalPlaneYResolution_);

      } else if (this->compareName("GainControl",name)) {
        if (this->readXMPType(xml,name,value)) {
          gainControl_ = this->gainControlType(value);
        }

      } else if (this->compareName("ImageUniqueID",name)) {
        this->readXMPString(xml,name,imageUniqueID_);

      } else if (this->compareName("ISOSpeedRatings",name)) {
        this->readXMPStringArray(xml,name,ISOSpeedRatings_);

      } else if (this->compareName("LightSource",name)) {
        if (this->readXMPType(xml,name,value)) {
          lightSource_ = this->lightSourceType(value);
        }

      } else if (this->compareName("MaxApertureValue",name)) {
        this->readXMPRationalUnsigned(xml,name,maxAperture_);

      } else if (this->compareName("MeteringMode",name)) {
        if (this->readXMPType(xml,name,value)) {
          meteringMode_ = this->meteringModeType(value);
        }

      } else if (this->compareName("PixelXDimension",name)) {
        this->readXMPString(xml,name,pixelXDimension_);

      } else if (this->compareName("PixelYDimension",name)) {
        this->readXMPString(xml,name,pixelYDimension_);

      } else if (this->compareName("RelatedSoundFile",name)) {
        this->readXMPString(xml,name,relatedSoundFile_);

      } else if (this->compareName("Saturation",name)) {
        if (this->readXMPType(xml,name,value)) {
          saturation_ = this->saturationType(value);
        }

      } else if (this->compareName("SceneCaptureType",name)) {
        if (this->readXMPType(xml,name,value)) {
          sceneCaptureType_ = this->sceneCaptureType(value);
        }

      } else if (this->compareName("SensingMethod",name)) {
        if (this->readXMPType(xml,name,value)) {
          sensingMethod_ = this->sensingMethodType(value);
        }

      } else if (this->compareName("Sharpness",name)) {
        if (this->readXMPType(xml,name,value)) {
          sharpness_ = this->sharpnessType(value);
        }

      } else if (this->compareName("ShutterSpeedValue",name)) {
        this->readXMPRationalUnsigned(xml,name,shutterSpeed_);

      } else if (this->compareName("SpectralSensitivity",name)) {
        this->readXMPString(xml,name,spectralSensitivity_);

      } else if (this->compareName("SubjectDistance",name)) {
        this->readXMPRationalUnsigned(xml,name,subjectDistance_);

      } else if (this->compareName("SubjectDistanceRange",name)) {
        if (this->readXMPType(xml,name,value)) {
          subjectDistanceRange_ = this->subjectDistanceRangeType(value);
        }

      } else if (this->compareName("SubjectLocation",name)) {
        this->readXMPStringArray(xml,name,subjectLocation_);

      } else if (this->compareName("WhiteBalance",name)) {
        if (this->readXMPType(xml,name,value)) {
          whiteBalance_ = this->whiteBalanceType(value);
        }

      //--------------------------------------------------------------------------
      // GPS entries
      //--------------------------------------------------------------------------
      } else if (this->compareName("GPSAltitude",name)) {
        this->readXMPRationalUnsigned(xml,name,gpsAltitude_);

      } else if (this->compareName("GPSAltitudeRef",name)) {
        if (this->readXMPType(xml,name,value)) {
          gpsAltitudeRef_ = this->GPSAltitudeType(value);
        }

      } else if (this->compareName("GPSDestBearing",name)) {
        this->readXMPRationalUnsigned(xml,name,gpsDestBearing_);

      } else if (this->compareName("GPSDestBearingRef",name)) {
        if (this->readXMPType(xml,name,text)) {
          gpsDestBearingRef_ = this->GPSDirectionType(text);
        }

      } else if (this->compareName("GPSDestDistance",name)) {
        this->readXMPRationalUnsigned(xml,name,gpsDestDistance_);

      } else if (this->compareName("GPSDestDistanceRef",name)) {
        if (this->readXMPType(xml,name,text)) {
          gpsDestDistanceRef_ = this->GPSDistanceType(text);
        }

      } else if (this->compareName("GPSDestLatitude",name)) {
        this->readXMPRationalUnsignedArray(xml,name,gpsDestLatitude_);

      } else if (this->compareName("GPSDestLongitude",name)) {
        this->readXMPRationalUnsignedArray(xml,name,gpsDestLongitude_);

      } else if (this->compareName("GPSDifferential",name)) {
        if (this->readXMPType(xml,name,value)) {
          gpsDifferential_ = this->GPSDifferentialType(value);
        }

      } else if (this->compareName("GPSDOP",name)) {
        this->readXMPRationalUnsigned(xml,name,gpsDOP_);

      } else if (this->compareName("GPSImgDirection",name)) {
        this->readXMPRationalUnsigned(xml,name,gpsImgDirection_);

      } else if (this->compareName("GPSImgDirectionRef",name)) {
        if (this->readXMPType(xml,name,text)) {
          gpsImgDirectionRef_ = this->GPSDirectionType(text);
        }

      } else if (this->compareName("GPSLatitudeRef",name)) {
        if (this->readXMPType(xml,name,text)) {
          gpsLatitudeRef_ = this->GPSLatitudeType(text);
        }

      } else if (this->compareName("GPSLatitude",name)) {
        this->readXMPRationalUnsignedArray(xml,name,gpsLatitude_);

      } else if (this->compareName("GPSLongitudeRef",name)) {
        if (this->readXMPType(xml,name,text)) {
          gpsLongitudeRef_ = this->GPSLongitudeType(text);
        }

      } else if (this->compareName("GPSLongitude",name)) {
        this->readXMPRationalUnsignedArray(xml,name,gpsLongitude_);

      } else if (this->compareName("GPSMapDatum",name)) {
        this->readXMPString(xml,name,gpsMapDatum_);

      } else if (this->compareName("GPSMeasureMode",name)) {
        if (this->readXMPType(xml,name,text)) {
          gpsMeasureMode_ = this->GPSMeasureModeType(text);
        }

      } else if (this->compareName("GPSSatellites",name)) {
        this->readXMPString(xml,name,gpsSatellites_);

      } else if (this->compareName("GPSSpeed",name)) {
        this->readXMPRationalUnsigned(xml,name,gpsSpeed_);

      } else if (this->compareName("GPSSpeedRef",name)) {
        if (this->readXMPType(xml,name,text)) {
          gpsSpeedRef_ = this->GPSSpeedType(text);
        }

      } else if (this->compareName("GPSStatus",name)) {
        if (this->readXMPType(xml,name,text)) {
          gpsStatus_ = this->GPSStatusType(text);
        }

      } else if (this->compareName("GPSTimeStamp",name)) {
        this->readXMPRationalUnsignedArray(xml,name,gpsTimeStamp_);

      } else if (this->compareName("GPSTrack",name)) {
        this->readXMPRationalUnsigned(xml,name,gpsTrack_);

      } else if (this->compareName("GPSTrackRef",name)) {
        if (this->readXMPType(xml,name,text)) {
          gpsTrackRef_ = this->GPSDirectionType(text);
        }

      //--------------------------------------------------------------------------
      // XMP entries
      //--------------------------------------------------------------------------
      } else if (this->compareName("Lens",name)) {
        this->readXMPString(xml,name,lens_);

      } else if (this->compareName("SerialNumber",name)) {
        this->readXMPString(xml,name,serialNumber_);

      //--------------------------------------------------------------------------
      // Unknown entry
      //--------------------------------------------------------------------------
      } else {
        qDebug() << "Unknown start element" << name;

        debugXMPText_ = "Not applicable";

      }

      //--------------------------------------------------------------------------
      // XMP metadata debugging information
      //--------------------------------------------------------------------------
      this->debugXMP();

    } else {

    }
  }

  //------------------------------------------------------------------------------
  // Error handling
  //------------------------------------------------------------------------------
  if (xml.hasError()) {
    qWarning() << xml.errorString() << xml.lineNumber() << xml.columnNumber();
  }

  //------------------------------------------------------------------------------
  // Clear XML reader
  //------------------------------------------------------------------------------
  xml.clear();
}

//--------------------------------------------------------------------------------
// Read IFD
//--------------------------------------------------------------------------------
void QImageMetaData::readIFD(QIODevice& data,quint32 position)
{
  //------------------------------------------------------------------------------
  // Position
  //------------------------------------------------------------------------------
  data.seek(static_cast<qint64>(position));

  //------------------------------------------------------------------------------
  // Input stream
  //------------------------------------------------------------------------------
  QDataStream* input = new QDataStream(&data);

  input->setByteOrder(endianness_);

  //------------------------------------------------------------------------------
  // Amount of entries
  //------------------------------------------------------------------------------
  quint16 amount;

  *input >> amount;

  //------------------------------------------------------------------------------
  // Debug
  //------------------------------------------------------------------------------
  qDebug() << "The amount of the entries in the IFD is" << amount;

  //------------------------------------------------------------------------------
  // Entries
  //------------------------------------------------------------------------------
  quint16 previousTag = 0;

  for (int i = 0;i < amount;++i) {
    //----------------------------------------------------------------------------
    // Fields
    //----------------------------------------------------------------------------
    quint16 tag;
    quint16 type;
    quint32 count;
    quint32 value;

    //----------------------------------------------------------------------------
    // Tag
    //----------------------------------------------------------------------------
    *input >> tag;

    definedTags_.append(tag);

    if (tag < previousTag) {
      qWarning() << "Tags should be in ascending order";
      qWarning() << "Tag" << previousTag << "is followed by tag" << tag;
    }

    //----------------------------------------------------------------------------
    // Debug
    //----------------------------------------------------------------------------
    qDebug() << "The data position is" << data.pos() << "and the order number of the entry is" << i + 1;

    //----------------------------------------------------------------------------
    // Type
    //----------------------------------------------------------------------------
    *input >> type;

    //----------------------------------------------------------------------------
    // Count
    //----------------------------------------------------------------------------
    *input >> count;

    //----------------------------------------------------------------------------
    // Value
    //----------------------------------------------------------------------------
    if (!this->leftJustified(type,count)) {
      *input >> value;

    } else {
      value = this->justify(data,type);
    }

    //----------------------------------------------------------------------------
    // Debug
    //----------------------------------------------------------------------------
    qDebug() << "Tag, type, count, and value of the entry are" << tag << type << count << value;

    //----------------------------------------------------------------------------
    // Sanity checks
    //----------------------------------------------------------------------------
    if (this->verifyEntry(tag,type,count,value)) {
      //--------------------------------------------------------------------------
      // Warnings
      //--------------------------------------------------------------------------
      if (warningCount_ > warningLimit_) {
        break;
      }

      switch (tag) {
        case QIMAGEMETADATA_IMAGEWIDTH: {
          width_ = value;
          break;
        }

        case QIMAGEMETADATA_IMAGELENGTH: {
          length_ = value;
          break;
        }

        case QIMAGEMETADATA_BITSPERSAMPLE: {
          depth_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_COMPRESSION: {
          compression_ = this->compressionType(value);
          break;
        }

        case QIMAGEMETADATA_PHOTOMETRICINTERPRETATION: {
          photometric_ = this->photometricInterpretationType(value);
          break;
        }

        case QIMAGEMETADATA_THRESHOLDING: {
          thresholding_ = value;
          break;
        }

        case QIMAGEMETADATA_CELLWIDTH: {
          cellWidth_ = value;
          break;
        }

        case QIMAGEMETADATA_CELLLENGTH: {
          cellLength_ = value;
          break;
        }

        case QIMAGEMETADATA_FILLORDER: {
          fillOrder_ = value;
          break;
        }

        case QIMAGEMETADATA_DOCUMENTNAME: {
          documentName_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_IMAGEDESCRIPTION: {
          imageDescription_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_MAKE: {
          make_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_MODEL: {
          model_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_STRIPOFFSETS: {
          stripOffsets_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_ORIENTATION: {
          orientation_ = this->orientationType(value);
          break;
        }

        case QIMAGEMETADATA_SAMPLESPERPIXEL: {
          samples_ = value;
          break;
        }

        case QIMAGEMETADATA_ROWSPERSTRIP: {
          rowsPerStrip_ = value;
          break;
        }

        case QIMAGEMETADATA_STRIPBYTECOUNTS: {
          stripByteCounts_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_MINSAMPLEVALUE: {
          minSampleValue_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_MAXSAMPLEVALUE: {
          maxSampleValue_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_XRESOLUTION: {
          xResolution_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_YRESOLUTION: {
          yResolution_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_PLANARCONFIGURATION: {
          planar_ = this->planarConfigurationType(value);
          break;
        }

        case QIMAGEMETADATA_PAGENAME: {
          pageName_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_XPOSITION: {
          xPosition_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_YPOSITION: {
          yPosition_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_FREEOFFSETS: {
          freeOffsets_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_FREEBYTECOUNTS: {
          freeByteCounts_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_GRAYRESPONSEUNIT: {
          grayResponseUnit_ = value;
          break;
        }

        case QIMAGEMETADATA_GRAYRESPONSECURVE: {
          grayResponseCurve_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_T4OPTIONS: {
          T4Options_ = value;
          break;
        }

        case QIMAGEMETADATA_T6OPTIONS: {
          T6Options_ = value;
          break;
        }

        case QIMAGEMETADATA_RESOLUTIONUNIT: {
          resolution_ = this->resolutionUnitType(value);
          break;
        }

        case QIMAGEMETADATA_PAGENUMBER: {
          pageNumber_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_TRANSFERFUNCTION: {
          transferFunction_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_SOFTWARE: {
          software_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_DATETIME: {
          dateAndTime_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_ARTIST: {
          artist_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_HOSTCOMPUTER: {
          hostComputer_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_PREDICTOR: {
          predictor_ = value;
          break;
        }

        case QIMAGEMETADATA_WHITEPOINT: {
          whitePoint_ = this->readRationalArray(data,count,value);
          break;
        }

        case QIMAGEMETADATA_PRIMARYCHROMATICITIES: {
          primaryChromaticities_ = this->readRationalArray(data,count,value);
          break;
        }

        case QIMAGEMETADATA_COLORMAP: {
          colorMap_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_HALFTONEHINTS: {
          halfToneHints_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_TILEWIDTH: {
          tileWidth_ = value;
          break;
        }

        case QIMAGEMETADATA_TILELENGTH: {
          tileLength_ = value;
          break;
        }

        case QIMAGEMETADATA_TILEOFFSETS: {
          tileOffsets_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_TILEBYTECOUNTS: {
          tileByteCounts_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_INKSET: {
          inkSet_ = value;
          break;
        }

        case QIMAGEMETADATA_INKNAMES: {
          inkNames_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_NUMBEROFINKS: {
          numberOfInks_ = value;
          break;
        }

        case QIMAGEMETADATA_DOTRANGE: {
          dotRange_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_TARGETPRINTER: {
          targetPrinter_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_EXTRASAMPLES: {
          extraSamples_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_SAMPLEFORMAT: {
          sampleFormat_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_TRANSFERRANGE: {
          transferRange_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_YCBCRCOEFFICIENTS: {
          yCbCrCoefficients_ = this->readRationalArray(data,count,value);
          break;
        }

        case QIMAGEMETADATA_YCBCRSUBSAMPLING: {
          yCbCrSubSampling_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_YCBCRPOSITIONING: {
          yCbCrPositioning_ = this->yCbCrPositioningType(value);
          break;
        }

        case QIMAGEMETADATA_REFERENCEBLACKWHITE: {
          referenceBlackWhite_ = this->readRationalArray(data,count,value);
          break;
        }

        case QIMAGEMETADATA_XMP: {
          qint64 bookmark = data.pos();

          this->displayXMP(data,count,value + static_cast<quint32>(baseOffset_));

          QString xmp = this->readString(data,count,value + static_cast<quint32>(baseOffset_));

          this->readXMP(xmp);

          data.seek(bookmark);

          break;
        }

        case QIMAGEMETADATA_COPYRIGHT: {
          copyright_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_EXPOSURETIME: {
          exposureTime_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_FNUMBER: {
          fNumber_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_EXPOSUREPROGRAM: {
          exposureProgram_ = this->exposureProgramType(value);
          break;
        }

        case QIMAGEMETADATA_SPECTRALSENSITIVITY: {
          spectralSensitivity_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_SHUTTERSPEEDVALUE: {
          shutterSpeed_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_APERTUREVALUE: {
          aperture_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_BRIGHTNESSVALUE: {
          brightness_ = this->readSRational(data,value);
          break;
        }

        case QIMAGEMETADATA_EXPOSUREBIASVALUE: {
          exposureBias_ = this->readSRational(data,value);
          break;
        }

        case QIMAGEMETADATA_MAXAPERTUREVALUE: {
          maxAperture_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_SUBJECTDISTANCE: {
          subjectDistance_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_METERINGMODE: {
          meteringMode_ = this->meteringModeType(value);
          break;
        }

        case QIMAGEMETADATA_EXIF: {
          qint64 bookmark = data.pos();

          this->readIFD(data,value + static_cast<quint32>(baseOffset_));

          data.seek(bookmark);

          break;
        }

        case QIMAGEMETADATA_GPS: {
          qint64 bookmark = data.pos();

          this->readIFD(data,value + static_cast<quint32>(baseOffset_));

          data.seek(bookmark);

          break;
        }

        case QIMAGEMETADATA_ISOSPEEDRATINGS: {
          ISOSpeedRatings_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_EXIFVERSION: {
          exifVersion_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_DATETIMEORIGINAL: {
          dateAndTimeOriginal_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_DATETIMEDIGITIZED: {
          dateAndTimeDigitized_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_LIGHTSOURCE: {
          lightSource_ = this->lightSourceType(value);
          break;
        }

        case QIMAGEMETADATA_FLASH: {
          flash_ = value;

          flashStatus_   = this->flashStatusType();
          flashStrobe_   = this->flashStrobeType();
          flashMode_     = this->flashModeType();
          flashFunction_ = this->flashFunctionType();
          flashRedEye_   = this->flashRedEeyeType();

          break;
        }

        case QIMAGEMETADATA_FOCALLENGTH: {
          focalLength_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_SUBJECTAREA: {
          subjectArea_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_FLASHENERGY: {
          flashEnergy_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_SUBSECTIME: {
          dateAndTimeSubseconds_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_SUBSECTIMEORIGINAL: {
          dateAndTimeOriginalSubseconds_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_SUBSECTIMEDIGITIZED: {
          dateAndTimeDigitizedSubseconds_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_FLASHPIXVERSION: {
          flashPixVersion_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_COLORSPACE: {
          colorSpace_ = this->colorSpaceType(value);
          break;
        }

        case QIMAGEMETADATA_PIXELXDIMENSION: {
          pixelXDimension_ = value;
          break;
        }

        case QIMAGEMETADATA_PIXELYDIMENSION: {
          pixelYDimension_ = value;
          break;
        }

        case QIMAGEMETADATA_FOCALPLANEXRESOLUTION: {
          focalPlaneXResolution_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_FOCALPLANEYRESOLUTION: {
          focalPlaneYResolution_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_FOCALPLANERESOLUTIONUNIT: {
          focalPlaneResolution_ = this->resolutionUnitType(value);
          break;
        }

        case QIMAGEMETADATA_SUBJECTLOCATION: {
          subjectLocation_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_EXPOSUREINDEX: {
          exposureIndex_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_SENSINGMETHOD: {
          sensingMethod_ = this->sensingMethodType(value);
          break;
        }

        case QIMAGEMETADATA_CUSTOMRENDERED: {
          customRendered_ = this->customRenderedType(value);
          break;
        }

        case QIMAGEMETADATA_EXPOSUREMODE: {
          exposureMode_ = this->exposureModeType(value);
          break;
        }

        case QIMAGEMETADATA_WHITEBALANCE: {
          whiteBalance_ = this->whiteBalanceType(value);
          break;
        }

        case QIMAGEMETADATA_DIGITALZOOMRATIO: {
          digitalZoomRatio_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_FOCALLENGTHIN35MMFILM: {
          focalLength35mm_ = value;
          break;
        }

        case QIMAGEMETADATA_SCENECAPTURETYPE: {
          sceneCaptureType_ = this->sceneCaptureType(value);
          break;
        }

        case QIMAGEMETADATA_GAINCONTROL: {
          gainControl_ = this->gainControlType(value);
          break;
        }

        case QIMAGEMETADATA_CONTRAST: {
          contrast_ = this->contrastType(value);
          break;
        }

        case QIMAGEMETADATA_SATURATION: {
          saturation_ = this->saturationType(value);
          break;
        }

        case QIMAGEMETADATA_SHARPNESS: {
          sharpness_ = this->sharpnessType(value);
          break;
        }

        case QIMAGEMETADATA_SUBJECTDISTANCERANGE: {
          subjectDistanceRange_ = this->subjectDistanceRangeType(value);
          break;
        }

        case QIMAGEMETADATA_COMPRESSEDBITSPERPIXEL: {
          compressedBitsPerPixel_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_COMPONENTSCONFIGURATION: {
          componentsConfiguration_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_RELATEDSOUNDFILE: {
          relatedSoundFile_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_IMAGEUNIQUEID: {
          imageUniqueID_ = this->readString(data,count,value);
          break;
        }

        //--------------------------------------------------------------------------
        // GPS tags
        //--------------------------------------------------------------------------
        case QIMAGEMETADATA_GPSVERSIONID: {
          gpsVersion_ = this->readArray(data,type,count,value);
          break;
        }

        case QIMAGEMETADATA_GPSLATITUDEREF: {
          gpsLatitudeRef_ = this->GPSLatitudeType(this->readString(data,count,value));
          break;
        }

        case QIMAGEMETADATA_GPSLATITUDE: {
          gpsLatitude_ = this->readRationalArray(data,count,value);
          break;
        }

        case QIMAGEMETADATA_GPSLONGITUDEREF: {
          gpsLongitudeRef_ = this->GPSLongitudeType(this->readString(data,count,value));
          break;
        }

        case QIMAGEMETADATA_GPSLONGITUDE: {
          gpsLongitude_ = this->readRationalArray(data,count,value);
          break;
        }

        case QIMAGEMETADATA_GPSALTITUDEREF: {
          gpsAltitudeRef_ = this->GPSAltitudeType(value);
          break;
        }

        case QIMAGEMETADATA_GPSALTITUDE: {
          gpsAltitude_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_GPSTIMESTAMP: {
          gpsTimeStamp_ = this->readRationalArray(data,count,value);
          break;
        }

        case QIMAGEMETADATA_GPSSATELLITES: {
          gpsSatellites_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_GPSSTATUS: {
          gpsStatus_ = this->GPSStatusType(this->readString(data,count,value));
          break;
        }

        case QIMAGEMETADATA_GPSMEASUREMODE: {
          gpsMeasureMode_ = this->GPSMeasureModeType(this->readString(data,count,value));
          break;
        }

        case QIMAGEMETADATA_GPSDOP: {
          gpsDOP_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_GPSSPEEDREF: {
          gpsSpeedRef_ = this->GPSSpeedType(this->readString(data,count,value));
          break;
        }

        case QIMAGEMETADATA_GPSSPEED: {
          gpsSpeed_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_GPSTRACKREF: {
          gpsTrackRef_ = this->GPSDirectionType(this->readString(data,count,value));
          break;
        }

        case QIMAGEMETADATA_GPSTRACK: {
          gpsTrack_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_GPSIMGDIRECTIONREF: {
          gpsImgDirectionRef_ = this->GPSDirectionType(this->readString(data,count,value));
          break;
        }

        case QIMAGEMETADATA_GPSIMGDIRECTION: {
          gpsImgDirection_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_GPSMAPDATUM: {
          gpsMapDatum_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_GPSDESTLATITUDEREF: {
          gpsDestLatitudeRef_ = this->GPSLatitudeType(this->readString(data,count,value));
          break;
        }

        case QIMAGEMETADATA_GPSDESTLATITUDE: {
          gpsDestLatitude_ = this->readRationalArray(data,count,value);
          break;
        }

        case QIMAGEMETADATA_GPSDESTLONGITUDEREF: {
          gpsDestLongitudeRef_ = this->GPSLongitudeType(this->readString(data,count,value));
          break;
        }

        case QIMAGEMETADATA_GPSDESTLONGITUDE: {
          gpsDestLatitude_ = this->readRationalArray(data,count,value);
          break;
        }

        case QIMAGEMETADATA_GPSDESTBEARINGREF: {
          gpsDestBearingRef_ = this->GPSDirectionType(this->readString(data,count,value));
          break;
        }

        case QIMAGEMETADATA_GPSDESTBEARING: {
          gpsDestBearing_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_GPSDESTDISTANCEREF: {
          gpsDestDistanceRef_ = this->GPSDistanceType(this->readString(data,count,value));
          break;
        }

        case QIMAGEMETADATA_GPSDESTDISTANCE: {
          gpsDestDistance_ = this->readRational(data,value);
          break;
        }

        case QIMAGEMETADATA_GPSDATESTAMP: {
          gpsDateStamp_ = this->readString(data,count,value);
          break;
        }

        case QIMAGEMETADATA_GPSDIFFERENTIAL: {
          gpsDifferential_ = this->GPSDifferentialType(value);
          break;
        }

        default: {
          qDebug() << "Unknown tag" << tag << "is ignored";

          unsupportedTags_.append(tag);
        }
      } // Switch
    } // If
  } // For

  //------------------------------------------------------------------------------
  // Offset to the next IFD
  //------------------------------------------------------------------------------
  *input >> tiffOffset_;

  if (tiffOffset_ == 0)
    tiffValid_ = false;
}

//--------------------------------------------------------------------------------
// Read - dataname
//--------------------------------------------------------------------------------
bool QImageMetaData::read(QString fileName)
{
  //------------------------------------------------------------------------------
  // Open data
  //------------------------------------------------------------------------------
  QFile file(fileName);

  if (!file.open(QIODevice::ReadOnly)) {
    errorCode_ = ErrorCodeFileNotOpened;

    errorMessage_ = QString("Could not open file %1.").arg(fileName);

    return false;
  }

  //------------------------------------------------------------------------------
  // Read
  //------------------------------------------------------------------------------
  bool result = this->read(file);

  //------------------------------------------------------------------------------
  // Close file
  //------------------------------------------------------------------------------
  file.close();

  //------------------------------------------------------------------------------
  // Return
  //------------------------------------------------------------------------------
  return result;
}

//--------------------------------------------------------------------------------
// Read - file
//--------------------------------------------------------------------------------
bool QImageMetaData::read(QIODevice& data)
{
  //------------------------------------------------------------------------------
  // Identify image format
  //------------------------------------------------------------------------------
  if (!this->identify(data)) {
    return false;
  }

  //------------------------------------------------------------------------------
  // Other errors
  //------------------------------------------------------------------------------
  if (errorCode_ != ErrorCodeUndefined) {
    return false;
  }

  //------------------------------------------------------------------------------
  // TIFF IFDs
  //
  // The EXIF IFD is called inside the TIFF IFD
  //
  // The GPS IFD is called inside the EXIF or TIFF IFD
  //------------------------------------------------------------------------------
  if (imageFormat_ == ImageFormatTIFF || imageFormat_ == ImageFormatJPEG) {
    while (tiffValid_ == true) {
      this->readIFD(data,tiffOffset_);

      //--------------------------------------------------------------------------
      // Errors
      //--------------------------------------------------------------------------
      if (errorCode_ != ErrorCodeUndefined)
        break;

      //--------------------------------------------------------------------------
      // Warnings
      //--------------------------------------------------------------------------
      if (warningCount_ > warningLimit_) {
        errorCode_ = ErrorCodeWarningLimitExceeded;

        errorMessage_ = QString("The metadata could not be read, because there were too many warnings.");

        break;
      }

      //--------------------------------------------------------------------------
      // JPEG
      //--------------------------------------------------------------------------
      if (imageFormat_ == QImageMetaData::ImageFormatJPEG)
        break;
    }

    //----------------------------------------------------------------------------
    // Return
    //----------------------------------------------------------------------------
    if (warningCount_ > warningLimit_) {
      errorMessage_ = "The amount of warnings exceeded the warning limit.";

      return false;
    } else {
      return true;
    }

  //------------------------------------------------------------------------------
  // PNG text information
  //------------------------------------------------------------------------------
  } else {
    //----------------------------------------------------------------------------
    // Find iTXt chunks
    //----------------------------------------------------------------------------
    this->findPNGTextChunks(data);

    //----------------------------------------------------------------------------
    // Read iTXt chunks
    //----------------------------------------------------------------------------
    this->readPNGTextChunks(data);

    //----------------------------------------------------------------------------
    // Return
    //----------------------------------------------------------------------------
    return true;
  }
}

//------------------------------------------------------------------------------
// Verify entry
//------------------------------------------------------------------------------
bool QImageMetaData::verifyEntry(quint16 tag,quint16 type,quint32 count,quint32 value) {
  //----------------------------------------------------------------------------
  // Result
  //----------------------------------------------------------------------------
  bool result = true;

  //----------------------------------------------------------------------------
  // Definitions of allowed types and counts
  //----------------------------------------------------------------------------
  QMap<quint32,quint32> defined_type;
  QMap<quint32,quint32> defined_count;
  QMap<quint32,QString> defined_name;

  //----------------------------------------------------------------------------
  // Definitions of tags
  //----------------------------------------------------------------------------

  //----------------------------------------------------------------------------
  // Types
  //----------------------------------------------------------------------------

  //----------------------------------------------------------------------------
  // TIFF
  //----------------------------------------------------------------------------
  defined_type.insert(QIMAGEMETADATA_IMAGEWIDTH               ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_IMAGELENGTH              ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_BITSPERSAMPLE            ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_COMPRESSION              ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_PHOTOMETRICINTERPRETATION,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_THRESHOLDING             ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_CELLWIDTH                ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_CELLLENGTH               ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_FILLORDER                ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_DOCUMENTNAME             ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_IMAGEDESCRIPTION         ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_MAKE                     ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_MODEL                    ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_STRIPOFFSETS             ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_ORIENTATION              ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_SAMPLESPERPIXEL          ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_ROWSPERSTRIP             ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_STRIPBYTECOUNTS          ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_MINSAMPLEVALUE           ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_MAXSAMPLEVALUE           ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_XRESOLUTION              ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_YRESOLUTION              ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_PLANARCONFIGURATION      ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_PAGENAME                 ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_XPOSITION                ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_YPOSITION                ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_FREEOFFSETS              ,QIMAGEMETADATA_LONG);
  defined_type.insert(QIMAGEMETADATA_FREEBYTECOUNTS           ,QIMAGEMETADATA_LONG);
  defined_type.insert(QIMAGEMETADATA_GRAYRESPONSEUNIT         ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_GRAYRESPONSECURVE        ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_T4OPTIONS                ,QIMAGEMETADATA_LONG);
  defined_type.insert(QIMAGEMETADATA_T6OPTIONS                ,QIMAGEMETADATA_LONG);
  defined_type.insert(QIMAGEMETADATA_RESOLUTIONUNIT           ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_PAGENUMBER               ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_TRANSFERFUNCTION         ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_SOFTWARE                 ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_DATETIME                 ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_ARTIST                   ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_HOSTCOMPUTER             ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_PREDICTOR                ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_WHITEPOINT               ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_PRIMARYCHROMATICITIES    ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_COLORMAP                 ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_HALFTONEHINTS            ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_TILEWIDTH                ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_TILELENGTH               ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_TILEOFFSETS              ,QIMAGEMETADATA_LONG);
  defined_type.insert(QIMAGEMETADATA_TILEBYTECOUNTS           ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_INKSET                   ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_INKNAMES                 ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_NUMBEROFINKS             ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_DOTRANGE                 ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_TARGETPRINTER            ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_EXTRASAMPLES             ,QIMAGEMETADATA_BYTE);
  defined_type.insert(QIMAGEMETADATA_SAMPLEFORMAT             ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_TRANSFERRANGE            ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_YCBCRCOEFFICIENTS        ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_YCBCRSUBSAMPLING         ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_YCBCRPOSITIONING         ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_REFERENCEBLACKWHITE      ,QIMAGEMETADATA_LONG);
  defined_type.insert(QIMAGEMETADATA_COPYRIGHT                ,QIMAGEMETADATA_ASCII);

  //----------------------------------------------------------------------------
  // EXIF
  //----------------------------------------------------------------------------
  defined_type.insert(QIMAGEMETADATA_EXIFVERSION             ,QIMAGEMETADATA_UNDEFINED);
  defined_type.insert(QIMAGEMETADATA_COLORSPACE              ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_COMPONENTSCONFIGURATION ,QIMAGEMETADATA_UNDEFINED);
  defined_type.insert(QIMAGEMETADATA_COMPRESSEDBITSPERPIXEL  ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_PIXELXDIMENSION         ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_PIXELYDIMENSION         ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_RELATEDSOUNDFILE        ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_FLASHPIXVERSION         ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_DATETIMEORIGINAL        ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_DATETIMEDIGITIZED       ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_SUBSECTIME              ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_SUBSECTIMEORIGINAL      ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_SUBSECTIMEDIGITIZED     ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_IMAGEUNIQUEID           ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_EXPOSURETIME            ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_FNUMBER                 ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_EXPOSUREPROGRAM         ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_SPECTRALSENSITIVITY     ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_ISOSPEEDRATINGS         ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_SHUTTERSPEEDVALUE       ,QIMAGEMETADATA_SRATIONAL);
  defined_type.insert(QIMAGEMETADATA_APERTUREVALUE           ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_BRIGHTNESSVALUE         ,QIMAGEMETADATA_SRATIONAL);
  defined_type.insert(QIMAGEMETADATA_EXPOSUREBIASVALUE       ,QIMAGEMETADATA_SRATIONAL);
  defined_type.insert(QIMAGEMETADATA_MAXAPERTUREVALUE        ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_SUBJECTDISTANCE         ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_METERINGMODE            ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_LIGHTSOURCE             ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_FLASH                   ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_FOCALLENGTH             ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_SUBJECTAREA             ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_FLASHENERGY             ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_FOCALPLANEXRESOLUTION   ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_FOCALPLANEYRESOLUTION   ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_FOCALPLANERESOLUTIONUNIT,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_SUBJECTLOCATION         ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_EXPOSUREINDEX           ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_SENSINGMETHOD           ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_CUSTOMRENDERED          ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_EXPOSUREMODE            ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_WHITEBALANCE            ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_DIGITALZOOMRATIO        ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_FOCALLENGTHIN35MMFILM   ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_SCENECAPTURETYPE        ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_GAINCONTROL             ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_CONTRAST                ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_SATURATION              ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_SHARPNESS               ,QIMAGEMETADATA_SHORT);
  defined_type.insert(QIMAGEMETADATA_SUBJECTDISTANCERANGE    ,QIMAGEMETADATA_SHORT);

  //----------------------------------------------------------------------------
  // GPS
  //----------------------------------------------------------------------------
  defined_type.insert(QIMAGEMETADATA_GPSVERSIONID       ,QIMAGEMETADATA_BYTE);
  defined_type.insert(QIMAGEMETADATA_GPSLATITUDEREF     ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_GPSLATITUDE        ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_GPSLONGITUDEREF    ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_GPSLONGITUDE       ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_GPSALTITUDEREF     ,QIMAGEMETADATA_BYTE);
  defined_type.insert(QIMAGEMETADATA_GPSALTITUDE        ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_GPSTIMESTAMP       ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_GPSSATELLITES      ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_GPSSTATUS          ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_GPSMEASUREMODE     ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_GPSDOP             ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_GPSSPEEDREF        ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_GPSSPEED           ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_GPSTRACKREF        ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_GPSTRACK           ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_GPSIMGDIRECTIONREF ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_GPSIMGDIRECTION    ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_GPSMAPDATUM        ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_GPSDESTLATITUDEREF ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_GPSDESTLATITUDE    ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_GPSDESTLONGITUDEREF,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_GPSDESTLONGITUDE   ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_GPSDESTBEARINGREF  ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_GPSDESTBEARING     ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_GPSDESTDISTANCEREF ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_GPSDESTDISTANCE    ,QIMAGEMETADATA_RATIONAL);
  defined_type.insert(QIMAGEMETADATA_GPSDATESTAMP       ,QIMAGEMETADATA_ASCII);
  defined_type.insert(QIMAGEMETADATA_GPSDIFFERENTIAL    ,QIMAGEMETADATA_SHORT);

  //----------------------------------------------------------------------------
  // Counts
  //----------------------------------------------------------------------------

  //----------------------------------------------------------------------------
  // TIFF
  //----------------------------------------------------------------------------
  defined_count.insert(QIMAGEMETADATA_IMAGEWIDTH               ,1);
  defined_count.insert(QIMAGEMETADATA_IMAGELENGTH              ,1);
  defined_count.insert(QIMAGEMETADATA_BITSPERSAMPLE            ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_COMPRESSION              ,1);
  defined_count.insert(QIMAGEMETADATA_PHOTOMETRICINTERPRETATION,1);
  defined_count.insert(QIMAGEMETADATA_THRESHOLDING             ,1);
  defined_count.insert(QIMAGEMETADATA_CELLWIDTH                ,1);
  defined_count.insert(QIMAGEMETADATA_CELLLENGTH               ,1);
  defined_count.insert(QIMAGEMETADATA_FILLORDER                ,1);
  defined_count.insert(QIMAGEMETADATA_DOCUMENTNAME             ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_IMAGEDESCRIPTION         ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_MAKE                     ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_MODEL                    ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_STRIPOFFSETS             ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_ORIENTATION              ,1);
  defined_count.insert(QIMAGEMETADATA_SAMPLESPERPIXEL          ,1);
  defined_count.insert(QIMAGEMETADATA_ROWSPERSTRIP             ,1);
  defined_count.insert(QIMAGEMETADATA_STRIPBYTECOUNTS          ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_MINSAMPLEVALUE           ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_MAXSAMPLEVALUE           ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_XRESOLUTION              ,1);
  defined_count.insert(QIMAGEMETADATA_YRESOLUTION              ,1);
  defined_count.insert(QIMAGEMETADATA_PLANARCONFIGURATION      ,1);
  defined_count.insert(QIMAGEMETADATA_PAGENAME                 ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_XPOSITION                ,1);
  defined_count.insert(QIMAGEMETADATA_YPOSITION                ,1);
  defined_count.insert(QIMAGEMETADATA_FREEOFFSETS              ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_FREEBYTECOUNTS           ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_GRAYRESPONSEUNIT         ,1);
  defined_count.insert(QIMAGEMETADATA_GRAYRESPONSECURVE        ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_T4OPTIONS                ,1);
  defined_count.insert(QIMAGEMETADATA_T6OPTIONS                ,1);
  defined_count.insert(QIMAGEMETADATA_RESOLUTIONUNIT           ,1);
  defined_count.insert(QIMAGEMETADATA_PAGENUMBER               ,1);
  defined_count.insert(QIMAGEMETADATA_TRANSFERFUNCTION         ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_SOFTWARE                 ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_DATETIME                 ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_ARTIST                   ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_HOSTCOMPUTER             ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_PREDICTOR                ,1);
  defined_count.insert(QIMAGEMETADATA_WHITEPOINT               ,2);
  defined_count.insert(QIMAGEMETADATA_PRIMARYCHROMATICITIES    ,6);
  defined_count.insert(QIMAGEMETADATA_COLORMAP                 ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_HALFTONEHINTS            ,2);
  defined_count.insert(QIMAGEMETADATA_TILEWIDTH                ,1);
  defined_count.insert(QIMAGEMETADATA_TILELENGTH               ,1);
  defined_count.insert(QIMAGEMETADATA_TILEOFFSETS              ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_TILEBYTECOUNTS           ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_INKSET                   ,1);
  defined_count.insert(QIMAGEMETADATA_INKNAMES                 ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_NUMBEROFINKS             ,1);
  defined_count.insert(QIMAGEMETADATA_DOTRANGE                 ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_TARGETPRINTER            ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_EXTRASAMPLES             ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_SAMPLEFORMAT             ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_TRANSFERRANGE            ,6);
  defined_count.insert(QIMAGEMETADATA_YCBCRCOEFFICIENTS        ,3);
  defined_count.insert(QIMAGEMETADATA_YCBCRSUBSAMPLING         ,2);
  defined_count.insert(QIMAGEMETADATA_YCBCRPOSITIONING         ,1);
  defined_count.insert(QIMAGEMETADATA_REFERENCEBLACKWHITE      ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_COPYRIGHT                ,QIMAGEMETADATA_ANY);

  //----------------------------------------------------------------------------
  // EXIF
  //----------------------------------------------------------------------------
  defined_count.insert(QIMAGEMETADATA_EXIFVERSION             ,4);
  defined_count.insert(QIMAGEMETADATA_COLORSPACE              ,1);
  defined_type.insert(QIMAGEMETADATA_COMPONENTSCONFIGURATION  ,4);
  defined_count.insert(QIMAGEMETADATA_COMPRESSEDBITSPERPIXEL  ,1);
  defined_count.insert(QIMAGEMETADATA_PIXELXDIMENSION         ,1);
  defined_count.insert(QIMAGEMETADATA_PIXELYDIMENSION         ,1);
  defined_count.insert(QIMAGEMETADATA_RELATEDSOUNDFILE        ,13);
  defined_count.insert(QIMAGEMETADATA_FLASHPIXVERSION         ,4);
  defined_count.insert(QIMAGEMETADATA_DATETIMEORIGINAL        ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_DATETIMEDIGITIZED       ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_SUBSECTIME              ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_SUBSECTIMEORIGINAL      ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_SUBSECTIMEDIGITIZED     ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_IMAGEUNIQUEID           ,33);
  defined_count.insert(QIMAGEMETADATA_EXPOSURETIME            ,1);
  defined_count.insert(QIMAGEMETADATA_FNUMBER                 ,1);
  defined_count.insert(QIMAGEMETADATA_EXPOSUREPROGRAM         ,1);
  defined_count.insert(QIMAGEMETADATA_SPECTRALSENSITIVITY     ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_ISOSPEEDRATINGS         ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_SHUTTERSPEEDVALUE       ,1);
  defined_count.insert(QIMAGEMETADATA_APERTUREVALUE           ,1);
  defined_count.insert(QIMAGEMETADATA_BRIGHTNESSVALUE         ,1);
  defined_count.insert(QIMAGEMETADATA_EXPOSUREBIASVALUE       ,1);
  defined_count.insert(QIMAGEMETADATA_MAXAPERTUREVALUE        ,1);
  defined_count.insert(QIMAGEMETADATA_SUBJECTDISTANCE         ,1);
  defined_count.insert(QIMAGEMETADATA_METERINGMODE            ,1);
  defined_count.insert(QIMAGEMETADATA_LIGHTSOURCE             ,1);
  defined_count.insert(QIMAGEMETADATA_FLASH                   ,1);
  defined_count.insert(QIMAGEMETADATA_FOCALLENGTH             ,1);
  defined_count.insert(QIMAGEMETADATA_SUBJECTAREA             ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_FLASHENERGY             ,1);
  defined_count.insert(QIMAGEMETADATA_FOCALPLANEXRESOLUTION   ,1);
  defined_count.insert(QIMAGEMETADATA_FOCALPLANEYRESOLUTION   ,1);
  defined_count.insert(QIMAGEMETADATA_FOCALPLANERESOLUTIONUNIT,1);
  defined_count.insert(QIMAGEMETADATA_SUBJECTLOCATION         ,1);
  defined_count.insert(QIMAGEMETADATA_EXPOSUREINDEX           ,1);
  defined_count.insert(QIMAGEMETADATA_SENSINGMETHOD           ,1);
  defined_count.insert(QIMAGEMETADATA_CUSTOMRENDERED          ,1);
  defined_count.insert(QIMAGEMETADATA_EXPOSUREMODE            ,1);
  defined_count.insert(QIMAGEMETADATA_WHITEBALANCE            ,1);
  defined_count.insert(QIMAGEMETADATA_DIGITALZOOMRATIO        ,1);
  defined_count.insert(QIMAGEMETADATA_FOCALLENGTHIN35MMFILM   ,1);
  defined_count.insert(QIMAGEMETADATA_SCENECAPTURETYPE        ,1);
  defined_count.insert(QIMAGEMETADATA_GAINCONTROL             ,1);
  defined_count.insert(QIMAGEMETADATA_CONTRAST                ,1);
  defined_count.insert(QIMAGEMETADATA_SATURATION              ,1);
  defined_count.insert(QIMAGEMETADATA_SHARPNESS               ,1);
  defined_count.insert(QIMAGEMETADATA_SUBJECTDISTANCERANGE    ,1);

  //----------------------------------------------------------------------------
  // GPS
  //----------------------------------------------------------------------------
  defined_count.insert(QIMAGEMETADATA_GPSVERSIONID       ,4);
  defined_count.insert(QIMAGEMETADATA_GPSLATITUDEREF     ,2);
  defined_count.insert(QIMAGEMETADATA_GPSLATITUDE        ,3);
  defined_count.insert(QIMAGEMETADATA_GPSLONGITUDEREF    ,2);
  defined_count.insert(QIMAGEMETADATA_GPSLONGITUDE       ,3);
  defined_count.insert(QIMAGEMETADATA_GPSALTITUDEREF     ,1);
  defined_count.insert(QIMAGEMETADATA_GPSALTITUDE        ,1);
  defined_count.insert(QIMAGEMETADATA_GPSTIMESTAMP       ,3);
  defined_count.insert(QIMAGEMETADATA_GPSSATELLITES      ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_GPSSTATUS          ,2);
  defined_count.insert(QIMAGEMETADATA_GPSMEASUREMODE     ,2);
  defined_count.insert(QIMAGEMETADATA_GPSDOP             ,1);
  defined_count.insert(QIMAGEMETADATA_GPSSPEEDREF        ,2);
  defined_count.insert(QIMAGEMETADATA_GPSSPEED           ,1);
  defined_count.insert(QIMAGEMETADATA_GPSTRACKREF        ,2);
  defined_count.insert(QIMAGEMETADATA_GPSTRACK           ,1);
  defined_count.insert(QIMAGEMETADATA_GPSIMGDIRECTIONREF ,2);
  defined_count.insert(QIMAGEMETADATA_GPSIMGDIRECTION    ,1);
  defined_count.insert(QIMAGEMETADATA_GPSMAPDATUM        ,QIMAGEMETADATA_ANY);
  defined_count.insert(QIMAGEMETADATA_GPSDESTLATITUDEREF ,2);
  defined_count.insert(QIMAGEMETADATA_GPSDESTLATITUDE    ,3);
  defined_count.insert(QIMAGEMETADATA_GPSDESTLONGITUDEREF,2);
  defined_count.insert(QIMAGEMETADATA_GPSDESTLONGITUDE   ,3);
  defined_count.insert(QIMAGEMETADATA_GPSDESTBEARINGREF  ,2);
  defined_count.insert(QIMAGEMETADATA_GPSDESTBEARING     ,1);
  defined_count.insert(QIMAGEMETADATA_GPSDESTDISTANCEREF ,2);
  defined_count.insert(QIMAGEMETADATA_GPSDESTDISTANCE    ,1);
  defined_count.insert(QIMAGEMETADATA_GPSDATESTAMP       ,11);
  defined_count.insert(QIMAGEMETADATA_GPSDIFFERENTIAL    ,1);

  //----------------------------------------------------------------------------
  // Names
  //----------------------------------------------------------------------------

  //----------------------------------------------------------------------------
  // TIFF
  //----------------------------------------------------------------------------
  defined_name.insert(QIMAGEMETADATA_IMAGEWIDTH               ,"image width");
  defined_name.insert(QIMAGEMETADATA_IMAGELENGTH              ,"image length");
  defined_name.insert(QIMAGEMETADATA_BITSPERSAMPLE            ,"bits per sample");
  defined_name.insert(QIMAGEMETADATA_COMPRESSION              ,"compression");
  defined_name.insert(QIMAGEMETADATA_PHOTOMETRICINTERPRETATION,"photometric interpretation");
  defined_name.insert(QIMAGEMETADATA_THRESHOLDING             ,"thresholding");
  defined_name.insert(QIMAGEMETADATA_CELLWIDTH                ,"cell width");
  defined_name.insert(QIMAGEMETADATA_CELLLENGTH               ,"cell length");
  defined_name.insert(QIMAGEMETADATA_FILLORDER                ,"fill order");
  defined_name.insert(QIMAGEMETADATA_DOCUMENTNAME             ,"document name");
  defined_name.insert(QIMAGEMETADATA_IMAGEDESCRIPTION         ,"image description");
  defined_name.insert(QIMAGEMETADATA_MAKE                     ,"manufacturer");
  defined_name.insert(QIMAGEMETADATA_MODEL                    ,"model");
  defined_name.insert(QIMAGEMETADATA_STRIPOFFSETS             ,"strip offsets");
  defined_name.insert(QIMAGEMETADATA_ORIENTATION              ,"orientation");
  defined_name.insert(QIMAGEMETADATA_SAMPLESPERPIXEL          ,"samples per pixel");
  defined_name.insert(QIMAGEMETADATA_ROWSPERSTRIP             ,"rows per strip");
  defined_name.insert(QIMAGEMETADATA_STRIPBYTECOUNTS          ,"strip byte counts");
  defined_name.insert(QIMAGEMETADATA_MINSAMPLEVALUE           ,"min sample value");
  defined_name.insert(QIMAGEMETADATA_MAXSAMPLEVALUE           ,"max sample value");
  defined_name.insert(QIMAGEMETADATA_XRESOLUTION              ,"x resolution");
  defined_name.insert(QIMAGEMETADATA_YRESOLUTION              ,"y resolution");
  defined_name.insert(QIMAGEMETADATA_PLANARCONFIGURATION      ,"planar configuration");
  defined_name.insert(QIMAGEMETADATA_PAGENAME                 ,"page name");
  defined_name.insert(QIMAGEMETADATA_XPOSITION                ,"x position");
  defined_name.insert(QIMAGEMETADATA_YPOSITION                ,"y position");
  defined_name.insert(QIMAGEMETADATA_FREEOFFSETS              ,"free offsets");
  defined_name.insert(QIMAGEMETADATA_FREEBYTECOUNTS           ,"free byte counts");
  defined_name.insert(QIMAGEMETADATA_GRAYRESPONSEUNIT         ,"gray response unit");
  defined_name.insert(QIMAGEMETADATA_GRAYRESPONSECURVE        ,"gray response curve");
  defined_name.insert(QIMAGEMETADATA_T4OPTIONS                ,"T4 options");
  defined_name.insert(QIMAGEMETADATA_T6OPTIONS                ,"T6 options");
  defined_name.insert(QIMAGEMETADATA_RESOLUTIONUNIT           ,"resolution unit");
  defined_name.insert(QIMAGEMETADATA_PAGENUMBER               ,"page number");
  defined_name.insert(QIMAGEMETADATA_TRANSFERFUNCTION         ,"transfer function");
  defined_name.insert(QIMAGEMETADATA_SOFTWARE                 ,"software");
  defined_name.insert(QIMAGEMETADATA_DATETIME                 ,"date and time");
  defined_name.insert(QIMAGEMETADATA_ARTIST                   ,"artist");
  defined_name.insert(QIMAGEMETADATA_HOSTCOMPUTER             ,"host computer");
  defined_name.insert(QIMAGEMETADATA_PREDICTOR                ,"predictor");
  defined_name.insert(QIMAGEMETADATA_WHITEPOINT               ,"white point");
  defined_name.insert(QIMAGEMETADATA_PRIMARYCHROMATICITIES    ,"primary chromaticities");
  defined_name.insert(QIMAGEMETADATA_COLORMAP                 ,"color map");
  defined_name.insert(QIMAGEMETADATA_HALFTONEHINTS            ,"half tone hints");
  defined_name.insert(QIMAGEMETADATA_TILEWIDTH                ,"tile width");
  defined_name.insert(QIMAGEMETADATA_TILELENGTH               ,"tile length");
  defined_name.insert(QIMAGEMETADATA_TILEOFFSETS              ,"tile offsets");
  defined_name.insert(QIMAGEMETADATA_TILEBYTECOUNTS           ,"tile byte counts");
  defined_name.insert(QIMAGEMETADATA_INKSET                   ,"ink set");
  defined_name.insert(QIMAGEMETADATA_INKNAMES                 ,"ink names");
  defined_name.insert(QIMAGEMETADATA_NUMBEROFINKS             ,"number of inks");
  defined_name.insert(QIMAGEMETADATA_DOTRANGE                 ,"dot range");
  defined_name.insert(QIMAGEMETADATA_TARGETPRINTER            ,"target printer");
  defined_name.insert(QIMAGEMETADATA_EXTRASAMPLES             ,"extra samples");
  defined_name.insert(QIMAGEMETADATA_SAMPLEFORMAT             ,"sample format");
  defined_name.insert(QIMAGEMETADATA_TRANSFERRANGE            ,"transfer range");
  defined_name.insert(QIMAGEMETADATA_YCBCRCOEFFICIENTS        ,"YCbCr coefficients");
  defined_name.insert(QIMAGEMETADATA_YCBCRSUBSAMPLING         ,"YCbCr subsampling");
  defined_name.insert(QIMAGEMETADATA_YCBCRPOSITIONING         ,"YCbCr positioning");
  defined_name.insert(QIMAGEMETADATA_REFERENCEBLACKWHITE      ,"reference black and white");
  defined_name.insert(QIMAGEMETADATA_COPYRIGHT                ,"copyright");

  //----------------------------------------------------------------------------
  // EXIF
  //----------------------------------------------------------------------------
  defined_name.insert(QIMAGEMETADATA_EXIFVERSION             ,"exif version");
  defined_name.insert(QIMAGEMETADATA_COLORSPACE              ,"color space");
  defined_name.insert(QIMAGEMETADATA_COMPONENTSCONFIGURATION ,"components configuration");
  defined_name.insert(QIMAGEMETADATA_COMPRESSEDBITSPERPIXEL  ,"compressed bits per pixel");
  defined_name.insert(QIMAGEMETADATA_PIXELXDIMENSION         ,"pixel x dimension");
  defined_name.insert(QIMAGEMETADATA_PIXELYDIMENSION         ,"pixel y dimension");
  defined_name.insert(QIMAGEMETADATA_RELATEDSOUNDFILE        ,"related sound file");
  defined_name.insert(QIMAGEMETADATA_FLASHPIXVERSION         ,"flash pix version");
  defined_name.insert(QIMAGEMETADATA_DATETIMEORIGINAL        ,"date and time original");
  defined_name.insert(QIMAGEMETADATA_DATETIMEDIGITIZED       ,"date and time digitized");
  defined_name.insert(QIMAGEMETADATA_SUBSECTIME              ,"subseconds");
  defined_name.insert(QIMAGEMETADATA_SUBSECTIMEORIGINAL      ,"subseconds original");
  defined_name.insert(QIMAGEMETADATA_SUBSECTIMEDIGITIZED     ,"sucseconds digitized");
  defined_name.insert(QIMAGEMETADATA_IMAGEUNIQUEID           ,"image unique ID");
  defined_name.insert(QIMAGEMETADATA_EXPOSURETIME            ,"exposure time");
  defined_name.insert(QIMAGEMETADATA_FNUMBER                 ,"f number");
  defined_name.insert(QIMAGEMETADATA_EXPOSUREPROGRAM         ,"exposure program");
  defined_name.insert(QIMAGEMETADATA_SPECTRALSENSITIVITY     ,"spectral sensitivity");
  defined_name.insert(QIMAGEMETADATA_ISOSPEEDRATINGS         ,"ISO speed ratings");
  defined_name.insert(QIMAGEMETADATA_SHUTTERSPEEDVALUE       ,"shutter speed");
  defined_name.insert(QIMAGEMETADATA_APERTUREVALUE           ,"aperture");
  defined_name.insert(QIMAGEMETADATA_BRIGHTNESSVALUE         ,"brightness");
  defined_name.insert(QIMAGEMETADATA_EXPOSUREBIASVALUE       ,"exposure bias");
  defined_name.insert(QIMAGEMETADATA_MAXAPERTUREVALUE        ,"max aperture");
  defined_name.insert(QIMAGEMETADATA_SUBJECTDISTANCE         ,"subject distance");
  defined_name.insert(QIMAGEMETADATA_METERINGMODE            ,"metering mode");
  defined_name.insert(QIMAGEMETADATA_LIGHTSOURCE             ,"light source");
  defined_name.insert(QIMAGEMETADATA_FLASH                   ,"flash");
  defined_name.insert(QIMAGEMETADATA_FOCALLENGTH             ,"focal length");
  defined_name.insert(QIMAGEMETADATA_SUBJECTAREA             ,"subject area");
  defined_name.insert(QIMAGEMETADATA_FLASHENERGY             ,"flash energy");
  defined_name.insert(QIMAGEMETADATA_FOCALPLANEXRESOLUTION   ,"focal plane x resolution");
  defined_name.insert(QIMAGEMETADATA_FOCALPLANEYRESOLUTION   ,"focal plane y resolution");
  defined_name.insert(QIMAGEMETADATA_FOCALPLANERESOLUTIONUNIT,"focal plane resolution unit");
  defined_name.insert(QIMAGEMETADATA_SUBJECTLOCATION         ,"subject location");
  defined_name.insert(QIMAGEMETADATA_EXPOSUREINDEX           ,"exposure index");
  defined_name.insert(QIMAGEMETADATA_SENSINGMETHOD           ,"sensing method");
  defined_name.insert(QIMAGEMETADATA_CUSTOMRENDERED          ,"custom rendered");
  defined_name.insert(QIMAGEMETADATA_EXPOSUREMODE            ,"exposure mode");
  defined_name.insert(QIMAGEMETADATA_WHITEBALANCE            ,"white balance");
  defined_name.insert(QIMAGEMETADATA_DIGITALZOOMRATIO        ,"digital zoom ratio");
  defined_name.insert(QIMAGEMETADATA_FOCALLENGTHIN35MMFILM   ,"focal length in 35mm film");
  defined_name.insert(QIMAGEMETADATA_SCENECAPTURETYPE        ,"scene capture type");
  defined_name.insert(QIMAGEMETADATA_GAINCONTROL             ,"gain control");
  defined_name.insert(QIMAGEMETADATA_CONTRAST                ,"contrast");
  defined_name.insert(QIMAGEMETADATA_SATURATION              ,"saturation");
  defined_name.insert(QIMAGEMETADATA_SHARPNESS               ,"sharpness");
  defined_name.insert(QIMAGEMETADATA_SUBJECTDISTANCERANGE    ,"subject distance range");

  //----------------------------------------------------------------------------
  // GPS
  //----------------------------------------------------------------------------
  defined_name.insert(QIMAGEMETADATA_GPSVERSIONID       ,"GPS version");
  defined_name.insert(QIMAGEMETADATA_GPSLATITUDEREF     ,"GPS reference latitude");
  defined_name.insert(QIMAGEMETADATA_GPSLATITUDE        ,"GPS latitude");
  defined_name.insert(QIMAGEMETADATA_GPSLONGITUDEREF    ,"GPS reference longitude");
  defined_name.insert(QIMAGEMETADATA_GPSLONGITUDE       ,"GPS longitude");
  defined_name.insert(QIMAGEMETADATA_GPSALTITUDEREF     ,"GPS reference altitude");
  defined_name.insert(QIMAGEMETADATA_GPSALTITUDE        ,"GPS altitude");
  defined_name.insert(QIMAGEMETADATA_GPSTIMESTAMP       ,"GPS time");
  defined_name.insert(QIMAGEMETADATA_GPSSATELLITES      ,"GPS satellites");
  defined_name.insert(QIMAGEMETADATA_GPSSTATUS          ,"GPS receiver status");
  defined_name.insert(QIMAGEMETADATA_GPSMEASUREMODE     ,"GPS measurement mode");
  defined_name.insert(QIMAGEMETADATA_GPSDOP             ,"GPS measurement precision");
  defined_name.insert(QIMAGEMETADATA_GPSSPEEDREF        ,"GPS reference speed");
  defined_name.insert(QIMAGEMETADATA_GPSSPEED           ,"GPS speed");
  defined_name.insert(QIMAGEMETADATA_GPSTRACKREF        ,"GPS reference track");
  defined_name.insert(QIMAGEMETADATA_GPSTRACK           ,"GPS track");
  defined_name.insert(QIMAGEMETADATA_GPSIMGDIRECTIONREF ,"GPS reference direction of the image");
  defined_name.insert(QIMAGEMETADATA_GPSIMGDIRECTION    ,"GPS direction of the image");
  defined_name.insert(QIMAGEMETADATA_GPSMAPDATUM        ,"GPS geodetic survey data");
  defined_name.insert(QIMAGEMETADATA_GPSDESTLATITUDEREF ,"GPS reference latitude of the destination");
  defined_name.insert(QIMAGEMETADATA_GPSDESTLATITUDE    ,"GPS latitude of the destination");
  defined_name.insert(QIMAGEMETADATA_GPSDESTLONGITUDEREF,"GPS reference longitude of the destination");
  defined_name.insert(QIMAGEMETADATA_GPSDESTLONGITUDE   ,"GPS longitude of the destination");
  defined_name.insert(QIMAGEMETADATA_GPSDESTBEARINGREF  ,"GPS reference bearing of the destination");
  defined_name.insert(QIMAGEMETADATA_GPSDESTBEARING     ,"GPS bearing of the destination");
  defined_name.insert(QIMAGEMETADATA_GPSDESTDISTANCEREF ,"GPS reference distance of the destination");
  defined_name.insert(QIMAGEMETADATA_GPSDESTDISTANCE    ,"GPS distance of the destination");
  defined_name.insert(QIMAGEMETADATA_GPSDATESTAMP       ,"GPS date");
  defined_name.insert(QIMAGEMETADATA_GPSDIFFERENTIAL    ,"GPS differential correction");

  //----------------------------------------------------------------------------
  // Iterators
  //----------------------------------------------------------------------------
  QMap<quint32,quint32>::const_iterator type_iterator  = defined_type.constBegin();
  QMap<quint32,quint32>::const_iterator count_iterator = defined_count.constBegin();

  //----------------------------------------------------------------------------
  // Verify the type
  //----------------------------------------------------------------------------
  while (type_iterator != defined_type.constEnd()) {
    if (type_iterator.key() == tag) {
      //------------------------------------------------------------------------
      // If the type is an unsigned integer,
      // let's allow all kind of unsigned integers
      //------------------------------------------------------------------------
      if (this->type_unsigned(type_iterator.value())) {
        if (!this->type_unsigned(type)) {
          qWarning() << "The type of the " << defined_name[tag] << "is illegal" << type;

          result = false;
        }

      //------------------------------------------------------------------------
      // Otherwise just check the type
      //------------------------------------------------------------------------
      } else {
        if (type != type_iterator.value()) {
          qWarning() << "The type of the " << defined_name[tag] << "is illegal" << type;

          result = false;
        }
      }
    }

    ++type_iterator;
  }

  //----------------------------------------------------------------------------
  // Verify the count
  //----------------------------------------------------------------------------
  while (count_iterator != defined_count.constEnd()) {
    if (count_iterator.key() == tag) {
      if (count_iterator.value() != QIMAGEMETADATA_ANY) {
        if (count != count_iterator.value()) {
          qWarning() << "The count of the " << defined_name[tag] << "is illegal" << count;

          result = false;
        }
      }

      if (defined_type[count_iterator.key()] == QIMAGEMETADATA_ASCII) {
        if (count > stringLimit_) {
          qWarning() << "The count of the " << defined_name[tag] << "exceeds the limit" << count;

          result = false;
        }
      } else {
        if (count > genericLimit_) {
          qWarning() << "The count of the " << defined_name[tag] << "exceeds the limit" << count;

          result = false;
        }
      }

    }

    ++count_iterator;
  }

  //----------------------------------------------------------------------------
  // Error codes
  //----------------------------------------------------------------------------
  if (tag == QIMAGEMETADATA_IMAGEWIDTH) {
    if (value == 0) {
      qWarning() << "The value of the " << defined_name[tag] << "is illegal" << value;

      result = false;
    }

    if (result == false) {
      errorCode_ = ErrorCodeImageWidthEntryIllegal;
    }

  } else if (tag == QIMAGEMETADATA_IMAGELENGTH) {
    if (value == 0) {
      qWarning() << "The value of the " << defined_name[tag] << "is illegal" << value;

      result = false;
    }

    if (result == false) {
      errorCode_ = ErrorCodeImageHeightEntryIllegal;
    }

  } else if (tag == QIMAGEMETADATA_PIXELXDIMENSION) {
    if (value == 0) {
      qWarning() << "The value of the " << defined_name[tag] << "is illegal" << value;

      result = false;
    }

    if (result == false) {
      errorCode_ = ErrorCodePixelXDimensionEntryIllegal;
    }

  } else if (tag == QIMAGEMETADATA_PIXELYDIMENSION) {
    if (value == 0) {
      qWarning() << "The value of the " << defined_name[tag] << "is illegal" << value;

      result = false;
    }

    if (result == false) {
      errorCode_ = ErrorCodePixelYDimensionEntryIllegal;
    }
  } else if (tag == QIMAGEMETADATA_CELLWIDTH) {
    if (value == 0) {
      qWarning() << "The value of the " << defined_name[tag] << "is illegal" << value;

      result = false;
    }

    if (result == false) {
      errorCode_ = ErrorCodeCellWidthEntryIllegal;
    }
  } else if (tag == QIMAGEMETADATA_CELLLENGTH) {
    if (value == 0) {
      qWarning() << "The value of the " << defined_name[tag] << "is illegal" << value;

      result = false;
    }

    if (result == false) {
      errorCode_ = ErrorCodeCellLengthEntryIllegal;
    }
  } else if (tag == QIMAGEMETADATA_TILEWIDTH) {
    if (value == 0) {
      qWarning() << "The value of the " << defined_name[tag] << "is illegal" << value;

      result = false;
    }

    if (result == false) {
      errorCode_ = ErrorCodeTileWidthEntryIllegal;
    }
  } else if (tag == QIMAGEMETADATA_TILELENGTH) {
    if (value == 0) {
      qWarning() << "The value of the " << defined_name[tag] << "is illegal" << value;

      result = false;
    }

    if (result == false) {
      errorCode_ = ErrorCodeTileLengthEntryIllegal;
    }
  }

  return result;
}

//--------------------------------------------------------------------------------
// Defined tags
//--------------------------------------------------------------------------------
QVector<quint32> QImageMetaData::definedTags()
{
  return definedTags_;
}

//--------------------------------------------------------------------------------
// Unsupported tags
//--------------------------------------------------------------------------------
QVector<quint32> QImageMetaData::unsupportedTags()
{
  return unsupportedTags_;
}

//--------------------------------------------------------------------------------
// Tags
//--------------------------------------------------------------------------------
QString QImageMetaData::imageDescription()
{
  return imageDescription_;
}

QString QImageMetaData::make()
{
  return make_;
}

QString QImageMetaData::model()
{
  return model_;
}

QString QImageMetaData::artist()
{
  return artist_;
}

quint32 QImageMetaData::width()
{
  return width_;
}

quint32 QImageMetaData::height()
{
  return length_;
}

QVector<quint32> QImageMetaData::depth()
{
  return depth_;
}

QImageMetaDataRational<quint32> QImageMetaData::exposureTime()
{
  return exposureTime_;
}

QImageMetaDataRational<quint32> QImageMetaData::shutterSpeed()
{
  return shutterSpeed_;
}

QVector<quint32> QImageMetaData::ISOSpeedRatings()
{
  return ISOSpeedRatings_;
}

QImageMetaDataRational<quint32> QImageMetaData::fNumber()
{
  return fNumber_;
}

QImageMetaDataRational<quint32> QImageMetaData::aperture()
{
  return aperture_;
}

QImageMetaDataRational<quint32> QImageMetaData::focalLength()
{
  return focalLength_;
}

quint32 QImageMetaData::focalLength35mm()
{
  return focalLength35mm_;
}

QImageMetaData::Compression QImageMetaData::compression()
{
  return compression_;
}

QImageMetaData::Photometric QImageMetaData::photometricInterpretation()
{
  return photometric_;
}

quint32 QImageMetaData::samples()
{
  return samples_;
}

qreal QImageMetaData::xResolution()
{
  return xResolution_.value();
}

qreal QImageMetaData::yResolution()
{
  return yResolution_.value();
}

QImageMetaData::PlanarConfiguration QImageMetaData::planarConfiguration()
{
  return planar_;
}

QImageMetaData::ResolutionUnit QImageMetaData::resolutionUnit()
{
  return resolution_;
}

QImageMetaData::Orientation QImageMetaData::orientation()
{
  return orientation_;
}

QString QImageMetaData::software()
{
  return software_;
}

QString QImageMetaData::dateAndTime()
{
  return dateAndTime_;
}

QString QImageMetaData::dateAndTimeSubseconds()
{
  return dateAndTimeSubseconds_;
}

QString QImageMetaData::dateAndTimeOriginal()
{
  return dateAndTimeOriginal_;
}

QString QImageMetaData::dateAndTimeOriginalSubseconds()
{
  return dateAndTimeOriginalSubseconds_;
}

QString QImageMetaData::dateAndTimeDigitized()
{
  return dateAndTimeDigitized_;
}

QString QImageMetaData::dateAndTimeDigitizedSubseconds()
{
  return dateAndTimeDigitizedSubseconds_;
}

QImageMetaData::ExposureProgram QImageMetaData::exposureProgram()
{
  return exposureProgram_;
}

QImageMetaData::LightSource QImageMetaData::lightSource()
{
  return lightSource_;
}

quint32 QImageMetaData::flash()
{
  return flash_;
}

QImageMetaData::FlashStatus QImageMetaData::flashStatus()
{
  return flashStatus_;
}

QImageMetaData::FlashStrobe QImageMetaData::flashStrobe()
{
  return flashStrobe_;
}

QImageMetaData::FlashMode QImageMetaData::flashMode()
{
  return flashMode_;
}

QImageMetaData::FlashFunction QImageMetaData::flashFunction()
{
  return flashFunction_;
}

QImageMetaData::FlashRedEye QImageMetaData::flashRedEye()
{
  return flashRedEye_;
}

qreal QImageMetaData::exposureBias()
{
  return exposureBias_.value();
}

qreal QImageMetaData::maxAperture()
{
  return maxAperture_.value();
}

QString QImageMetaData::copyright()
{
  return copyright_;
}

QImageMetaData::ColorSpace QImageMetaData::colorSpace()
{
  return colorSpace_;
}

quint32 QImageMetaData::pixelXDimension()
{
  return pixelXDimension_;
}

quint32 QImageMetaData::pixelYDimension()
{
  return pixelYDimension_;
}

qreal QImageMetaData::digitalZoomRatio()
{
  return digitalZoomRatio_.value();
}

QImageMetaData::GainControl QImageMetaData::gainControl()
{
  return gainControl_;
}

QImageMetaData::SensingMethod QImageMetaData::sensingMethod()
{
  return sensingMethod_;
}

QImageMetaData::CustomRendered QImageMetaData::customRendered()
{
  return customRendered_;
}

QImageMetaData::MeteringMode QImageMetaData::meteringMode()
{
  return meteringMode_;
}

QImageMetaData::ExposureMode QImageMetaData::exposureMode()
{
  return exposureMode_;
}

QImageMetaData::WhiteBalance QImageMetaData::whiteBalance()
{
  return whiteBalance_;
}

QImageMetaData::SceneCaptureType QImageMetaData::sceneCaptureType()
{
  return sceneCaptureType_;
}

QImageMetaData::Contrast QImageMetaData::contrast()
{
  return contrast_;
}

QImageMetaData::Saturation QImageMetaData::saturation()
{
  return saturation_;
}

QImageMetaData::Sharpness QImageMetaData::sharpness()
{
  return sharpness_;
}

QImageMetaData::SubjectDistanceRange QImageMetaData::subjectDistanceRange()
{
  return subjectDistanceRange_;
}

QVector<quint32> QImageMetaData::yCbCrSubSampling()
{
  return yCbCrSubSampling_;
}

QImageMetaData::YCbCrPositioning QImageMetaData::yCbCrPositioning()
{
  return yCbCrPositioning_;
}

qreal QImageMetaData::brightness()
{
  return brightness_.value();
}

qreal QImageMetaData::focalPlaneXResolution()
{
  return focalPlaneXResolution_.value();
}

qreal QImageMetaData::focalPlaneYResolution()
{
  return focalPlaneYResolution_.value();
}

QImageMetaData::ResolutionUnit QImageMetaData::focalPlaneResolutionUnit()
{
  return focalPlaneResolution_;
}

QString QImageMetaData::documentName()
{
  return documentName_;
}

QString QImageMetaData::pageName()
{
  return pageName_;
}

QString QImageMetaData::hostComputer()
{
  return hostComputer_;
}

quint32 QImageMetaData::rowsPerStrip()
{
  return rowsPerStrip_;
}

QVector<quint32> QImageMetaData::stripOffsets()
{
  return stripOffsets_;
}

QVector<quint32> QImageMetaData::stripByteCounts()
{
  return stripByteCounts_;
}

quint32 QImageMetaData::cellWidth()
{
  return cellWidth_;
}

quint32 QImageMetaData::cellLength()
{
  return cellLength_;
}

quint32 QImageMetaData::tileWidth()
{
  return tileWidth_;
}

quint32 QImageMetaData::tileLength()
{
  return tileLength_;
}

QVector<quint32> QImageMetaData::tileOffsets()
{
  return tileOffsets_;
}

QVector<quint32> QImageMetaData::tileByteCounts()
{
  return tileByteCounts_;
}

qreal QImageMetaData::compressedBitsPerPixel()
{
  return compressedBitsPerPixel_.value();
}

QString QImageMetaData::relatedSoundFile()
{
  return relatedSoundFile_;
}

QString QImageMetaData::imageUniqueID()
{
  return imageUniqueID_;
}

quint32 QImageMetaData::thresholding()
{
  return thresholding_;
}

quint32 QImageMetaData::fillOrder()
{
  return fillOrder_;
}

QVector<quint32> QImageMetaData::minSampleValue()
{
  return minSampleValue_;
}

QVector<quint32> QImageMetaData::maxSampleValue()
{
  return maxSampleValue_;
}

QImageMetaDataRational<quint32> QImageMetaData::xPosition()
{
  return xPosition_;
}

QImageMetaDataRational<quint32> QImageMetaData::yPosition()
{
  return yPosition_;
}

QVector<quint32> QImageMetaData::freeOffsets()
{
  return freeOffsets_;
}

QVector<quint32> QImageMetaData::freeByteCounts()
{
  return freeByteCounts_;
}

quint32 QImageMetaData::grayResponseUnit()
{
  return grayResponseUnit_;
}

QVector<quint32> QImageMetaData::grayResponseCurve()
{
  return grayResponseCurve_;
}

quint32 QImageMetaData::T4Options()
{
  return T4Options_;
}

quint32 QImageMetaData::T6Options()
{
  return T6Options_;
}

QVector<quint32> QImageMetaData::pageNumber()
{
  return pageNumber_;
}

QVector<quint32> QImageMetaData::transferFunction()
{
  return transferFunction_;
}

quint32 QImageMetaData::predictor()
{
  return predictor_;
}

QVector< QImageMetaDataRational<quint32> > QImageMetaData::whitePoint()
{
  return whitePoint_;
}

QVector< QImageMetaDataRational<quint32> > QImageMetaData::primaryChromaticities()
{
  return primaryChromaticities_;
}

QVector<quint32> QImageMetaData::colorMap()
{
  return colorMap_;
}

QVector<quint32> QImageMetaData::halfToneHints()
{
  return halfToneHints_;
}

QString QImageMetaData::spectralSensitivity()
{
  return spectralSensitivity_;
}

QImageMetaDataRational<quint32> QImageMetaData::subjectDistance()
{
  return subjectDistance_;
}

QVector<quint32> QImageMetaData::subjectArea()
{
  return subjectArea_;
}

QImageMetaDataRational<quint32> QImageMetaData::flashEnergy()
{
  return flashEnergy_;
}

QVector<quint32> QImageMetaData::subjectLocation()
{
  return subjectLocation_;
}

QImageMetaDataRational<quint32> QImageMetaData::exposureIndex()
{
  return exposureIndex_;
}

quint32 QImageMetaData::inkSet()
{
  return inkSet_;
}

QString QImageMetaData::inkNames()
{
  return inkNames_;
}

quint32 QImageMetaData::numberOfInks()
{
  return numberOfInks_;
}

QVector<quint32> QImageMetaData::dotRange()
{
  return dotRange_;
}

QString QImageMetaData::targetPrinter()
{
  return targetPrinter_;
}

QVector<quint32> QImageMetaData::extraSamples()
{
  return extraSamples_;
}

QVector<quint32> QImageMetaData::sampleFormat()
{
  return sampleFormat_;
}

QVector<quint32> QImageMetaData::transferRange()
{
  return transferRange_;
}

QVector< QImageMetaDataRational<quint32> > QImageMetaData::yCbCrCoefficients()
{
  return yCbCrCoefficients_;
}

QVector< QImageMetaDataRational<quint32> > QImageMetaData::referenceBlackWhite()
{
  return referenceBlackWhite_;
}

QString QImageMetaData::exifVersion()
{
  return exifVersion_;
}

QString QImageMetaData::flashPixVersion()
{
  return flashPixVersion_;
}

QVector<quint32> QImageMetaData::componentsConfiguration()
{
  return componentsConfiguration_;
}

bool QImageMetaData::gpsLocation() {
  if (gpsLatitudeRef_ == GPSLatitudeUndefined || gpsLatitudeRef_ == GPSLatitudeUnknown) {
    errorCode_ = ErrorCodeGPSLatitudeReferenceInvalid;

    errorMessage_ = QString("The GPS latitude reference is invalid.");

    return false;
  } else if (gpsLongitudeRef_ == GPSLongitudeUndefined || gpsLongitudeRef_ == GPSLongitudeUnknown) {
    errorCode_ = ErrorCodeGPSLongitudeReferenceInvalid;

    errorMessage_ = QString("The GPS longitude reference is invalid.");

    return false;
  } else if (gpsLatitude_.size() != 3) {
    errorCode_ = ErrorCodeGPSLatitudeInvalid;

    errorMessage_ = QString("The GPS latitude is invalid.");

    return false;
  } else if (gpsLatitude_[0].denominator() == 0) {
    errorCode_ = ErrorCodeGPSLatitudeInvalid;

    errorMessage_ = QString("The GPS latitude degrees is invalid.");

    return false;
  } else if (gpsLatitude_[1].denominator() == 0) {
    errorCode_ = ErrorCodeGPSLatitudeInvalid;

    errorMessage_ = QString("The GPS latitude minutes is invalid.");

    return false;
  } else if (gpsLatitude_[2].denominator() == 0) {
    errorCode_ = ErrorCodeGPSLatitudeInvalid;

    errorMessage_ = QString("The GPS latitude seconds is invalid.");

    return false;
  } else if (gpsLongitude_.size() != 3) {
    errorCode_ = ErrorCodeGPSLongitudeInvalid;

    errorMessage_ = QString("The GPS latitude is invalid.");

    return false;
  } else if (gpsLongitude_[0].denominator() == 0) {
    errorCode_ = ErrorCodeGPSLongitudeInvalid;

    errorMessage_ = QString("The GPS latitude degrees is invalid.");

    return false;
  } else if (gpsLongitude_[1].denominator() == 0) {
    errorCode_ = ErrorCodeGPSLongitudeInvalid;

    errorMessage_ = QString("The GPS latitude minutes is invalid.");

    return false;
  } else if (gpsLongitude_[2].denominator() == 0) {
    errorCode_ = ErrorCodeGPSLongitudeInvalid;

    errorMessage_ = QString("The GPS latitude seconds is invalid.");

    return false;
  } else {
    return true;
  }
}

QVector<quint32> QImageMetaData::gpsVersion()
{
  return gpsVersion_;
}

QImageMetaData::GPSLatitude QImageMetaData::gpsLatitudeRef()
{
  return gpsLatitudeRef_;
}

QVector< QImageMetaDataRational<quint32> > QImageMetaData::gpsLatitude()
{
  return gpsLatitude_;
}

qreal QImageMetaData::gpsLatitudeDegrees()
{
  if (gpsLatitude_.size() != 3) {
    return 0.0;
  } else {
    if (gpsLatitude_[0].denominator() == 0) {
      return 0.0;
    } else {
      return static_cast<qreal>(gpsLatitude_[0].nominator())/static_cast<qreal>(gpsLatitude_[0].denominator());
    }
  }
}

qreal QImageMetaData::gpsLatitudeMinutes()
{
  if (gpsLatitude_.size() != 3) {
    return 0.0;
  } else {
    if (gpsLatitude_[1].denominator() == 0) {
      return 0.0;
    } else {
      if (gpsLatitude_[1].denominator() == 1) {
        return static_cast<qreal>(gpsLatitude_[1].nominator());
      } else if (gpsLatitude_[1].denominator() == 100) {
        return static_cast<qreal>(gpsLatitude_[1].nominator()/gpsLatitude_[1].denominator());
      } else {
        return 0.0;
      }
    }
  }
}

qreal QImageMetaData::gpsLatitudeSeconds()
{
  if (gpsLatitude_.size() != 3) {
    return 0.0;
  } else {
    if (gpsLatitude_[1].denominator() == 0) {
      return 0.0;
    } else {
      if (gpsLatitude_[1].denominator() == 1) {
        return static_cast<qreal>(gpsLatitude_[2].nominator());
      } else if (gpsLatitude_[1].denominator() == 100) {
        return static_cast<qreal>(gpsLatitude_[1].nominator() % gpsLatitude_[1].denominator())*60.0/100.0;
      } else {
        return 0.0;
      }
    }
  }
}

QImageMetaData::GPSLongitude QImageMetaData::gpsLongitudeRef()
{
  return gpsLongitudeRef_;
}

QVector< QImageMetaDataRational<quint32> > QImageMetaData::gpsLongitude()
{
  return gpsLongitude_;
}

qreal QImageMetaData::gpsLongitudeDegrees()
{
  if (gpsLongitude_.size() != 3) {
    return 0.0;
  } else {
    if (gpsLongitude_[0].denominator() == 0) {
      return 0.0;
    } else {
      return static_cast<qreal>(gpsLongitude_[0].nominator())/static_cast<qreal>(gpsLongitude_[0].denominator());
    }
  }
}

qreal QImageMetaData::gpsLongitudeMinutes()
{
  if (gpsLongitude_.size() != 3) {
    return 0.0;
  } else {
    if (gpsLongitude_[1].denominator() == 0) {
      return 0.0;
    } else {
      if (gpsLongitude_[1].denominator() == 1) {
        return static_cast<qreal>(gpsLongitude_[1].nominator());
      } else if (gpsLongitude_[1].denominator() == 100) {
        return static_cast<qreal>(gpsLongitude_[1].nominator()/gpsLongitude_[1].denominator());
      } else {
        return 0.0;
      }
    }
  }
}

qreal QImageMetaData::gpsLongitudeSeconds()
{
  if (gpsLongitude_.size() != 3) {
    return 0.0;
  } else {
    if (gpsLongitude_[1].denominator() == 0) {
      return 0.0;
    } else {
      if (gpsLongitude_[1].denominator() == 1) {
        return static_cast<qreal>(gpsLongitude_[2].nominator());
      } else if (gpsLongitude_[1].denominator() == 100) {
        return static_cast<qreal>(gpsLongitude_[1].nominator() % gpsLongitude_[1].denominator())*60.0/100.0;
      } else {
        return 0.0;
      }
    }
  }
}


QImageMetaData::GPSAltitude QImageMetaData::gpsAltitudeRef()
{
  return gpsAltitudeRef_;
}

QImageMetaDataRational<quint32> QImageMetaData::gpsAltitude()
{
  return gpsAltitude_;
}

QVector< QImageMetaDataRational<quint32> > QImageMetaData::gpsTimeStamp()
{
  return gpsTimeStamp_;
}

QString QImageMetaData::gpsSatellites()
{
  return gpsSatellites_;
}

QImageMetaData::GPSStatus QImageMetaData::gpsStatus()
{
  return gpsStatus_;
}

QImageMetaData::GPSMeasureMode QImageMetaData::gpsMeasureMode()
{
  return gpsMeasureMode_;
}

QImageMetaDataRational<quint32> QImageMetaData::gpsDOP()
{
  return gpsDOP_;
}

QImageMetaData::GPSSpeed QImageMetaData::gpsSpeedRef()
{
  return gpsSpeedRef_;
}

QImageMetaDataRational<quint32> QImageMetaData::gpsSpeed()
{
  return gpsSpeed_;
}

QImageMetaData::GPSDirection QImageMetaData::gpsTrackRef()
{
  return gpsTrackRef_;
}

QImageMetaDataRational<quint32> QImageMetaData::gpsTrack()
{
  return gpsTrack_;
}

QImageMetaData::GPSDirection QImageMetaData::gpsImgDirectionRef()
{
  return gpsImgDirectionRef_;
}

QImageMetaDataRational<quint32> QImageMetaData::gpsImgDirection()
{
  return gpsImgDirection_;
}

QString QImageMetaData::gpsMapDatum()
{
  return gpsMapDatum_;
}

QImageMetaData::GPSLatitude QImageMetaData::gpsDestLatitudeRef()
{
  return gpsDestLatitudeRef_;
}

QVector< QImageMetaDataRational<quint32> > QImageMetaData::gpsDestLatitude()
{
  return gpsDestLatitude_;
}

QImageMetaData::GPSLongitude QImageMetaData::gpsDestLongitudeRef()
{
  return gpsDestLongitudeRef_;
}

QVector< QImageMetaDataRational<quint32> > QImageMetaData::gpsDestLongitude()
{
  return gpsDestLongitude_;
}

QImageMetaData::GPSDirection QImageMetaData::gpsDestBearingRef()
{
  return gpsDestBearingRef_;
}

QImageMetaDataRational<quint32> QImageMetaData::gpsDestBearing()
{
  return gpsDestBearing_;
}

QImageMetaData::GPSDistance QImageMetaData::gpsDestDistanceRef()
{
  return gpsDestDistanceRef_;
}

QImageMetaDataRational<quint32> QImageMetaData::gpsDestDistance()
{
  return gpsDestDistance_;
}

QString QImageMetaData::gpsDateStamp()
{
  return gpsDateStamp_;
}

quint32 QImageMetaData::gpsDifferential()
{
  return gpsDifferential_;
}

//--------------------------------------------------------------------------------
// XMP tags
//--------------------------------------------------------------------------------
QString QImageMetaData::lens()
{
  return lens_;
}

QString QImageMetaData::serialNumber()
{
  return serialNumber_;
}

//--------------------------------------------------------------------------------
// Limits
//--------------------------------------------------------------------------------
void QImageMetaData::stringLimit(quint32 limit)
{
  stringLimit_ = limit;
}

void QImageMetaData::genericLimit(quint32 limit)
{
  genericLimit_ = limit;
}

//--------------------------------------------------------------------------------
// Type unsigned
//--------------------------------------------------------------------------------
bool QImageMetaData::type_unsigned(quint32 type) {
  if (type == QIMAGEMETADATA_BYTE  ||
      type == QIMAGEMETADATA_SHORT ||
      type == QIMAGEMETADATA_LONG) {
    return true;
  } else {
    return false;
  }
}

//--------------------------------------------------------------------------------
// Error message
//--------------------------------------------------------------------------------
QString QImageMetaData::errorMessage()
{
  return errorMessage_;
}

//--------------------------------------------------------------------------------
// Warning limit
//--------------------------------------------------------------------------------
void QImageMetaData::warningLimit(quint32 limit) {
  warningLimit_ = limit;
}

//--------------------------------------------------------------------------------
// Orientation type
//--------------------------------------------------------------------------------
QImageMetaData::Orientation QImageMetaData::orientationType(quint32 value) {
  if (value == 1) {
    return OrientationTopLeft;
  } else if (value == 2) {
    return OrientationTopRight;
  } else if (value == 3) {
    return OrientationBottomRight;
  } else if (value == 4) {
    return OrientationBottomLeft;
  } else if (value == 5) {
    return OrientationLeftTop;
  } else if (value == 6) {
    return OrientationRightTop;
  } else if (value == 7) {
    return OrientationRightBottom;
  } else if (value == 8) {
    return OrientationLeftBottom;
  } else {
    qWarning() << "The value of the orientation (274) is unknown" << value;

    return OrientationUnknown;
  }
}

//--------------------------------------------------------------------------------
// Compression type
//--------------------------------------------------------------------------------
QImageMetaData::Compression QImageMetaData::compressionType(quint32 value) {
  if (value == 1) {
    return CompressionUncompressed;
  } else if (value == 2) {
    return CompressionCCIT1D;
  } else if (value == 3) {
    return CompressionGroup3Fax;
  } else if (value == 4) {
    return CompressionGroup4Fax;
  } else if (value == 5) {
    return CompressionLZW;
  } else if (value == 6) {
    return CompressionJPEG;
  } else if (value == 32773) {
    return CompressionPackBits;
  } else {
    qWarning() << "The value of the compression tag (259) is unknown" << value;

    return CompressionUnknown;
  }
}

//--------------------------------------------------------------------------------
// Photometric interpretation type
//--------------------------------------------------------------------------------
QImageMetaData::Photometric QImageMetaData::photometricInterpretationType(quint32 value) {
  if (value == 0) {
    return PhotometricWhiteIsZero;
  } else if (value == 1) {
    return PhotometricBlackIsZero;
  } else if (value == 2) {
    return PhotometricRGB;
  } else if (value == 3) {
    return PhotometricRGBPalette;
  } else if (value == 4) {
    return PhotometricTransparencyMask;
  } else if (value == 5) {
    return PhotometricCMYK;
  } else if (value == 6) {
    return PhotometricYCbCr;
  } else if (value == 7) {
    return PhotometricCIELab;
  } else {
    qWarning() << "The value of the photometric tag (262) is unknown" << value;

    return PhotometricUnknown;
  }
}

QImageMetaData::PlanarConfiguration QImageMetaData::planarConfigurationType(quint32 value) {
  if (value == 1) {
    return PlanarChunky;
  } else if (value == 2) {
    return PlanarPlanar;
  } else {
    qWarning() << "The value of the planar configuration tag (284) is unknown" << value;

    return PlanarUnknown;
  }
}

QImageMetaData::ResolutionUnit QImageMetaData::resolutionUnitType(quint32 value) {
  if (value == 1) {
    return ResolutionNoUnit;
  } else if (value == 2) {
    return ResolutionInch;
  } else if (value == 3) {
    return ResolutionCentimeter;
  } else {
    qWarning() << "The value of the resolution unit tag (296) or the focal plane resolution unit tag (41488) is unknown" << value;

    return ResolutionUnknown;
  }
}

QImageMetaData::YCbCrPositioning QImageMetaData::yCbCrPositioningType(quint32 value) {
  if (value == 1) {
    return YCbCrPositioningCentered;
  } else if (value == 2) {
    return YCbCrPositioningCoSited;
  } else {
    qWarning() << "The value of the YCbCr positioning tag (531) is unknown" << value;

    return YCbCrPositioningUnknown;
  }
}

QImageMetaData::ExposureProgram QImageMetaData::exposureProgramType(quint32 value) {
  if (value == 0) {
    return ExposureProgramNotDefined;
  } else if (value == 1) {
    return ExposureProgramManual;
  } else if (value == 2) {
    return ExposureProgramNormal;
  } else if (value == 3) {
    return ExposureProgramAperturePriority;
  } else if (value == 4) {
    return ExposureProgramShutterPriority;
  } else if (value == 5) {
    return ExposureProgramCreative;
  } else if (value == 6) {
    return ExposureProgramAction;
  } else if (value == 7) {
    return ExposureProgramPortrait;
  } else if (value == 8) {
    return ExposureProgramLandscape;
  } else {
    qWarning() << "The value of the exposure program (34850) is unknown" << value;

    return ExposureProgramUnknown;
  }
}

QImageMetaData::MeteringMode QImageMetaData::meteringModeType(quint32 value) {
  if (value == 1) {
    return MeteringModeAverage;
  } else if (value == 2) {
    return MeteringModeCenterWeightedAverage;
  } else if (value == 3) {
    return MeteringModeSpot;
  } else if (value == 4) {
    return MeteringModeMultiSpot;
  } else if (value == 5) {
    return MeteringModePattern;
  } else if (value == 6) {
    return MeteringModePartial;
  } else {
    qWarning() << "The value of the metering mode (37383) is unknown" << value;

    return MeteringModeUnknown;
  }
}

QImageMetaData::LightSource QImageMetaData::lightSourceType(quint32 value) {
  if (value == 0) {
    return LightSourceUnknown;
  } else if (value == 1) {
    return LightSourceDaylight;
  } else if (value == 2) {
    return LightSourceFluorescent;
  } else if (value == 3) {
    return LightSourceTungsten;
  } else if (value == 4) {
    return LightSourceFlash;
  } else if (value == 9) {
    return LightSourceFineWeather;
  } else if (value == 10) {
    return LightSourceCloudyWeather;
  } else if (value == 11) {
    return LightSourceShade;
  } else if (value == 12) {
    return LightSourceDaylightFluorescent;
  } else if (value == 13) {
    return LightSourceDayWhiteFluorescent;
  } else if (value == 14) {
    return LightSourceCoolWhiteFluorescent;
  } else if (value == 15) {
    return LightSourceWhiteFluorescent;
  } else if (value == 17) {
    return LightSourceStandardLightA;
  } else if (value == 18) {
    return LightSourceStandardLightB;
  } else if (value == 19) {
    return LightSourceStandardLightC;
  } else if (value == 20) {
    return LightSourceD55;
  } else if (value == 21) {
    return LightSourceD65;
  } else if (value == 22) {
    return LightSourceD75;
  } else if (value == 23) {
    return LightSourceD50;
  } else if (value == 24) {
    return LightSourceISOStudioTungsten;
  } else if (value == 255) {
    return LightSourceOther;
  } else {
    return LightSourceUnknown;

    qWarning() << "The value of the light source tag (37384) is unknown" << value;
  }
}

QImageMetaData::SensingMethod QImageMetaData::sensingMethodType(quint32 value) {
  if (value == 1) {
    return SensingMethodNotDefined;
  } else if (value == 2) {
    return SensingMethodOneChipColorAreaSensor;
  } else if (value == 3) {
    return SensingMethodTwoChipColorAreaSensor;
  } else if (value == 4) {
    return SensingMethodThreeChipColorAreaSensor;
  } else if (value == 5) {
    return SensingMethodColorSequentialSensor;
  } else if (value == 6) {
    return SensingMethodTrilinearSensor;
  } else if (value == 7) {
    return SensingMethodColorSequentialLinearSensor;
  } else if (value == 8) {
    return SensingMethodUndefined;
  } else {
    qWarning() << "The value of the sensing method tag (41495) is unknown" << value;

    return SensingMethodUnknown;
  }
}

QImageMetaData::CustomRendered QImageMetaData::customRenderedType(quint32 value) {
  if (value == 0) {
    return CustomRenderedNormal;
  } else if (value == 1) {
    return CustomRenderedCustom;
  } else {
    qWarning() << "The value of the custom rendered tag (41985) is unknown" << value;

    return CustomRenderedUnknown;
  }
}

QImageMetaData::ExposureMode QImageMetaData::exposureModeType(quint32 value) {
  if (value == 0) {
    return ExposureModeAuto;
  } else if (value == 1) {
    return ExposureModeManual;
  } else if (value == 2) {
    return ExposureModeAutoBracket;
  } else {
    qWarning() << "The value of the exposure mode tag (41986) is unknown" << value;

    return ExposureModeUnknown;
  }
}

QImageMetaData::WhiteBalance QImageMetaData::whiteBalanceType(quint32 value) {
  if (value == 0) {
    return WhiteBalanceAuto;
  } else if (value == 1) {
    return WhiteBalanceManual;
  } else {
    qWarning() << "The value of the white balance tag (41987) is unknown" << value;

    return WhiteBalanceUnknown;
  }
}

QImageMetaData::SceneCaptureType QImageMetaData::sceneCaptureType(quint32 value) {
  if (value == 0) {
    return SceneCaptureTypeStandard;
  } else if (value == 1) {
    return SceneCaptureTypeLandscape;
  } else if (value == 2) {
    return SceneCaptureTypePortrait;
  } else if (value == 3) {
    return SceneCaptureTypeNight;
  } else {
    qWarning() << "The value of the scene capture type tag (41990) is unknown" << value;

    return SceneCaptureTypeUnknown;
  }
}

QImageMetaData::GainControl QImageMetaData::gainControlType(quint32 value) {
  if (value == 0) {
    return GainControlNone;
  } else if (value == 1) {
    return GainControlLowUp;
  } else if (value == 2) {
    return GainControlHighUp;
  } else if (value == 3) {
    return GainControlLowDown;
  } else if (value == 4) {
    return GainControlHighDown;
  } else {
    qWarning() << "The value of the gain control tag (41990) is unknown" << value;

    return GainControlUnknown;
  }
}

QImageMetaData::Contrast QImageMetaData::contrastType(quint32 value) {
  if (value == 0) {
    return ContrastNormal;
  } else if (value == 1) {
    return ContrastSoft;
  } else if (value == 2) {
    return ContrastHard;
  } else {
    qWarning() << "The value of the contrast tag (41992) is unknown" << value;

    return ContrastUnknown;
  }
}

QImageMetaData::Saturation QImageMetaData::saturationType(quint32 value) {
  if (value == 0) {
    return SaturationNormal;
  } else if (value == 1) {
    return SaturationLow;
  } else if (value == 2) {
    return SaturationHigh;
  } else {
    qWarning() << "The value of the saturation tag (41993) is unknown" << value;

    return SaturationUnknown;
  }
}

QImageMetaData::Sharpness QImageMetaData::sharpnessType(quint32 value) {
  if (value == 0) {
    return SharpnessNormal;
  } else if (value == 1) {
    return SharpnessSoft;
  } else if (value == 2) {
    return SharpnessHard;
  } else {
    qWarning() << "The value of the sharpness tag (41994) is unknown" << value;

    return SharpnessUnknown;
  }
}

QImageMetaData::SubjectDistanceRange QImageMetaData::subjectDistanceRangeType(quint32 value) {
  if (value == 0) {
    return SubjectDistanceRangeUnknown;
  } else if (value == 1) {
    return SubjectDistanceRangeMacro;
  } else if (value == 2) {
    return SubjectDistanceRangeCloseView;
  } else if (value == 3) {
    return SubjectDistanceRangeDistanceView;
  } else {
    qWarning() << "The value of the subject distance range tag (41996) is unknown" << value;

    return SubjectDistanceRangeUnknown;
  }
}

QImageMetaData::ColorSpace QImageMetaData::colorSpaceType(quint32 value) {
  if (value == 1) {
    return ColorSpacesRGB;
  } else if (value == 255) {
    return ColorSpaceUncalibrated;
  } else {
    qWarning() << "The value of the color space tag (40961) is unknown" << value;

    return ColorSpaceUnknown;
  }
}

QImageMetaData::FlashStatus QImageMetaData::flashStatusType() {
  const quint32 mask = 0x00000001;

  const quint32 flash = flash_ && mask;

  if (flash == 0) {
    return FlashStatusNotFired;
  } else {
    return FlashStatusFired;
  }
}

QImageMetaData::FlashStrobe QImageMetaData::flashStrobeType() {
  const quint32 mask = 0x00000006;

  const quint32 flash = (flash_ && mask) >> 1;

  if (flash == 0) {
    return FlashStrobeNoStrobeReturnDetection;
  } else if (flash == 2) {
    return FlashStrobeReturnLightNotDetected;
  } else if (flash == 3) {
    return FlashStrobeReturnLightDetected;
  } else {
    return FlashStrobeUnknown;
  }
}

QImageMetaData::FlashMode QImageMetaData::flashModeType() {
  const quint32 mask = 0x00000018;

  const quint32 flash = (flash_ && mask) >> 3;

  if (flash == 1) {
    return FlashModeCompulsoryFlashFiring;
  } else if (flash == 2) {
    return FlashModeCompulsoryFlashSuppression;
  } else if (flash == 3) {
    return FlashModeAuto;
  } else {
    return FlashModeUnknown;
  }
}

QImageMetaData::FlashFunction QImageMetaData::flashFunctionType() {
  const quint32 mask = 0x00000020;

  const quint32 flash = (flash_ && mask) >> 5;

  if (flash == 0) {
    return FlashFunctionEnabled;
  } else {
    return FlashFunctionDisabled;
  }
}

QImageMetaData::FlashRedEye QImageMetaData::flashRedEeyeType() {
  const quint32 mask = 0x00000040;

  const quint32 flash = (flash_ && mask) >> 6;

  if (flash == 0) {
    return FlashRedEyeDisabled;
  } else {
    return FlashRedEyeEnabled;
  }
}

QImageMetaData::GPSLatitude QImageMetaData::GPSLatitudeType(QString value)
{
  if (value.compare("N") == 0) {
    return GPSLatitudeNorth;
  } else if (value.compare("S") == 0) {
    return GPSLatitudeSouth;
  } else {
    return GPSLatitudeUnknown;
  }
}

QImageMetaData::GPSLongitude QImageMetaData::GPSLongitudeType(QString value)
{
  if (value.compare("E") == 0) {
    return GPSLongitudeEast;
  } else if (value.compare("W") == 0) {
    return GPSLongitudeWest;
  } else {
    return GPSLongitudeUnknown;
  }
}

QImageMetaData::GPSAltitude QImageMetaData::GPSAltitudeType(quint32 value)
{
  if (value == 0) {
    return GPSAltitudeAboveSeaLevel;
  } else if (value == 1) {
    return GPSAltitudeBelowSeaLevel;
  } else {
    return GPSAltitudeUnknown;
  }
}

QImageMetaData::GPSStatus QImageMetaData::GPSStatusType(QString value)
{
  if (value.compare("A") == 0) {
    return GPSStatusMeasurementInProgress;
  } else if (value.compare("V") == 0) {
    return GPSStatusInteroperability;
  } else {
    return GPSStatusUnknown;
  }
}

QImageMetaData::GPSMeasureMode QImageMetaData::GPSMeasureModeType(QString value)
{
  if (value.compare("2") == 0) {
    return GPSMeasureModeTwoDimensional;
  } else if (value.compare("3") == 0) {
    return GPSMeasureModeThreeDimensional;
  } else {
    return GPSMeasureModeUnknown;
  }
}

QImageMetaData::GPSSpeed QImageMetaData::GPSSpeedType(QString value)
{
  if (value.compare("K") == 0) {
    return GPSSpeedKilometers;
  } else if (value.compare("M") == 0) {
    return GPSSpeedMiles;
  } else if (value.compare("N") == 0) {
    return GPSSpeedKnots;
  } else {
    return GPSSpeedUnknown;
  }
}

QImageMetaData::GPSDirection QImageMetaData::GPSDirectionType(QString value)
{
  if (value.compare("T") == 0) {
    return GPSDirectionTrue;
  } else if (value.compare("M") == 0) {
    return GPSDirectionMagnetic;
  } else {
    return GPSDirectionUnknown;
  }
}

QImageMetaData::GPSDistance QImageMetaData::GPSDistanceType(QString value)
{
  if (value.compare("K") == 0) {
    return GPSDistanceKilometers;
  } else if (value.compare("M") == 0) {
    return GPSDistanceMiles;
  } else if (value.compare("N") == 0) {
    return GPSDistanceKnots;
  } else {
    return GPSDistanceUnknown;
  }
}

QImageMetaData::GPSDifferential QImageMetaData::GPSDifferentialType(quint32 value)
{
  if (value == 0) {
    return GPSDifferentialWithoutCorrection;
  } else if (value == 1) {
    return GPSDifferentialWithCorrection;
  } else {
    return GPSDifferentialUnknown;
  }
}

//--------------------------------------------------------------------------------
// XMP metadata debugging information
//--------------------------------------------------------------------------------
void QImageMetaData::debugXMP()
{
  qDebug() << "XMP Name:" << debugXMPName_ << "XMP Text:" << debugXMPText_;
}

void QImageMetaData::displayXMP(QIODevice& data,quint32 count,quint32 position)
{
  QString xml = this->readString(data,count,position);

  qDebug() << xml;
}
