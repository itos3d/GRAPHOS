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

#ifndef QIMAGEMETADATA_H
#define QIMAGEMETADATA_H

//--------------------------------------------------------------------------------
// Defines
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
// Types
//--------------------------------------------------------------------------------
#define QIMAGEMETADATA_BYTE                            1
#define QIMAGEMETADATA_ASCII                           2
#define QIMAGEMETADATA_SHORT                           3
#define QIMAGEMETADATA_LONG                            4
#define QIMAGEMETADATA_RATIONAL                        5
#define QIMAGEMETADATA_SBYTE                           6
#define QIMAGEMETADATA_UNDEFINED                       7
#define QIMAGEMETADATA_SSHORT                          9
#define QIMAGEMETADATA_SLONG                           9
#define QIMAGEMETADATA_SRATIONAL                      10
#define QIMAGEMETADATA_FLOAT                          11
#define QIMAGEMETADATA_DOUBLE                         12

//--------------------------------------------------------------------------------
// Counts
//--------------------------------------------------------------------------------
#define QIMAGEMETADATA_ANY                             0

//--------------------------------------------------------------------------------
// TIFF tags
//--------------------------------------------------------------------------------
#define QIMAGEMETADATA_NEWSUBFILETYPE                254
#define QIMAGEMETADATA_SUBFILETYPE                   255
#define QIMAGEMETADATA_IMAGEWIDTH                    256
#define QIMAGEMETADATA_IMAGELENGTH                   257
#define QIMAGEMETADATA_BITSPERSAMPLE                 258
#define QIMAGEMETADATA_COMPRESSION                   259
#define QIMAGEMETADATA_PHOTOMETRICINTERPRETATION     262
#define QIMAGEMETADATA_THRESHOLDING                  263
#define QIMAGEMETADATA_CELLWIDTH                     264
#define QIMAGEMETADATA_CELLLENGTH                    265
#define QIMAGEMETADATA_FILLORDER                     266
#define QIMAGEMETADATA_DOCUMENTNAME                  269
#define QIMAGEMETADATA_IMAGEDESCRIPTION              270
#define QIMAGEMETADATA_MAKE                          271
#define QIMAGEMETADATA_MODEL                         272
#define QIMAGEMETADATA_STRIPOFFSETS                  273
#define QIMAGEMETADATA_ORIENTATION                   274
#define QIMAGEMETADATA_SAMPLESPERPIXEL               277
#define QIMAGEMETADATA_ROWSPERSTRIP                  278
#define QIMAGEMETADATA_STRIPBYTECOUNTS               279
#define QIMAGEMETADATA_MINSAMPLEVALUE                280
#define QIMAGEMETADATA_MAXSAMPLEVALUE                281
#define QIMAGEMETADATA_XRESOLUTION                   282
#define QIMAGEMETADATA_YRESOLUTION                   283
#define QIMAGEMETADATA_PLANARCONFIGURATION           284
#define QIMAGEMETADATA_PAGENAME                      285
#define QIMAGEMETADATA_XPOSITION                     286
#define QIMAGEMETADATA_YPOSITION                     287
#define QIMAGEMETADATA_FREEOFFSETS                   288
#define QIMAGEMETADATA_FREEBYTECOUNTS                289
#define QIMAGEMETADATA_GRAYRESPONSEUNIT              290
#define QIMAGEMETADATA_GRAYRESPONSECURVE             291
#define QIMAGEMETADATA_T4OPTIONS                     292
#define QIMAGEMETADATA_T6OPTIONS                     293
#define QIMAGEMETADATA_RESOLUTIONUNIT                296
#define QIMAGEMETADATA_PAGENUMBER                    297
#define QIMAGEMETADATA_TRANSFERFUNCTION              301
#define QIMAGEMETADATA_SOFTWARE                      305
#define QIMAGEMETADATA_DATETIME                      306
#define QIMAGEMETADATA_ARTIST                        315
#define QIMAGEMETADATA_HOSTCOMPUTER                  316
#define QIMAGEMETADATA_PREDICTOR                     317
#define QIMAGEMETADATA_WHITEPOINT                    318
#define QIMAGEMETADATA_PRIMARYCHROMATICITIES         319
#define QIMAGEMETADATA_COLORMAP                      320
#define QIMAGEMETADATA_HALFTONEHINTS                 321
#define QIMAGEMETADATA_TILEWIDTH                     322
#define QIMAGEMETADATA_TILELENGTH                    323
#define QIMAGEMETADATA_TILEOFFSETS                   324
#define QIMAGEMETADATA_TILEBYTECOUNTS                325
#define QIMAGEMETADATA_INKSET                        332
#define QIMAGEMETADATA_INKNAMES                      333
#define QIMAGEMETADATA_NUMBEROFINKS                  334
#define QIMAGEMETADATA_DOTRANGE                      336
#define QIMAGEMETADATA_TARGETPRINTER                 337
#define QIMAGEMETADATA_EXTRASAMPLES                  338
#define QIMAGEMETADATA_SAMPLEFORMAT                  339
#define QIMAGEMETADATA_SMINSAMPLEVALUE               340
#define QIMAGEMETADATA_SMAXSAMPLEVALUE               341
#define QIMAGEMETADATA_TRANSFERRANGE                 342
#define QIMAGEMETADATA_JPEGPROC                      512
#define QIMAGEMETADATA_JPEGINTERCHANGEFORMAT         513
#define QIMAGEMETADATA_JPEGINTERCHANGEFORMATLENGTH   514
#define QIMAGEMETADATA_JPEGRESTARTINTERVAL           515
#define QIMAGEMETADATA_JPEGLOSSLESSPREDICTORS        517
#define QIMAGEMETADATA_JPEGPOINTTRANSFORMATIONS      518
#define QIMAGEMETADATA_JPEGQTABLES                   519
#define QIMAGEMETADATA_JPEGDCTABLES                  520
#define QIMAGEMETADATA_JPEGACTABLES                  521
#define QIMAGEMETADATA_YCBCRCOEFFICIENTS             529
#define QIMAGEMETADATA_YCBCRSUBSAMPLING              530
#define QIMAGEMETADATA_YCBCRPOSITIONING              531
#define QIMAGEMETADATA_REFERENCEBLACKWHITE           532
#define QIMAGEMETADATA_COPYRIGHT                   33432

//--------------------------------------------------------------------------------
// EXIF tags
//--------------------------------------------------------------------------------
#define QIMAGEMETADATA_EXIF                        34665
#define QIMAGEMETADATA_EXIFVERSION                 36864
#define QIMAGEMETADATA_FLASHPIXVERSION             40960
#define QIMAGEMETADATA_COLORSPACE                  40961
#define QIMAGEMETADATA_COMPONENTSCONFIGURATION     37121
#define QIMAGEMETADATA_COMPRESSEDBITSPERPIXEL      37122
#define QIMAGEMETADATA_PIXELXDIMENSION             40962
#define QIMAGEMETADATA_PIXELYDIMENSION             40963
#define QIMAGEMETADATA_MAKERNOTE                   37500
#define QIMAGEMETADATA_USERCOMMENT                 37510
#define QIMAGEMETADATA_RELATEDSOUNDFILE            40964
#define QIMAGEMETADATA_DATETIMEORIGINAL            36867
#define QIMAGEMETADATA_DATETIMEDIGITIZED           36868
#define QIMAGEMETADATA_SUBSECTIME                  37520
#define QIMAGEMETADATA_SUBSECTIMEORIGINAL          37521
#define QIMAGEMETADATA_SUBSECTIMEDIGITIZED         37522
#define QIMAGEMETADATA_IMAGEUNIQUEID               42016
#define QIMAGEMETADATA_EXPOSURETIME                33434
#define QIMAGEMETADATA_FNUMBER                     33437
#define QIMAGEMETADATA_EXPOSUREPROGRAM             34850
#define QIMAGEMETADATA_SPECTRALSENSITIVITY         34852
#define QIMAGEMETADATA_ISOSPEEDRATINGS             34855
#define QIMAGEMETADATA_OECF                        34856
#define QIMAGEMETADATA_SHUTTERSPEEDVALUE           37377
#define QIMAGEMETADATA_APERTUREVALUE               37378
#define QIMAGEMETADATA_BRIGHTNESSVALUE             37379
#define QIMAGEMETADATA_EXPOSUREBIASVALUE           37380
#define QIMAGEMETADATA_MAXAPERTUREVALUE            37381
#define QIMAGEMETADATA_SUBJECTDISTANCE             37382
#define QIMAGEMETADATA_METERINGMODE                37383
#define QIMAGEMETADATA_LIGHTSOURCE                 37384
#define QIMAGEMETADATA_FLASH                       37385
#define QIMAGEMETADATA_FOCALLENGTH                 37386
#define QIMAGEMETADATA_SUBJECTAREA                 37396
#define QIMAGEMETADATA_FLASHENERGY                 41483
#define QIMAGEMETADATA_SPATIALFREQUENCYRESPONSE    41484
#define QIMAGEMETADATA_FOCALPLANEXRESOLUTION       41486
#define QIMAGEMETADATA_FOCALPLANEYRESOLUTION       41487
#define QIMAGEMETADATA_FOCALPLANERESOLUTIONUNIT    41488
#define QIMAGEMETADATA_SUBJECTLOCATION             41492
#define QIMAGEMETADATA_EXPOSUREINDEX               41493
#define QIMAGEMETADATA_SENSINGMETHOD               41495
#define QIMAGEMETADATA_FILESOURCE                  41728
#define QIMAGEMETADATA_SCENETYPE                   41729
#define QIMAGEMETADATA_CFAPATTERN                  41730
#define QIMAGEMETADATA_CUSTOMRENDERED              41985
#define QIMAGEMETADATA_EXPOSUREMODE                41986
#define QIMAGEMETADATA_WHITEBALANCE                41987
#define QIMAGEMETADATA_DIGITALZOOMRATIO            41988
#define QIMAGEMETADATA_FOCALLENGTHIN35MMFILM       41989
#define QIMAGEMETADATA_SCENECAPTURETYPE            41990
#define QIMAGEMETADATA_GAINCONTROL                 41991
#define QIMAGEMETADATA_CONTRAST                    41992
#define QIMAGEMETADATA_SATURATION                  41993
#define QIMAGEMETADATA_SHARPNESS                   41994
#define QIMAGEMETADATA_DEVICESETTINGDESCRIPTION    41995
#define QIMAGEMETADATA_SUBJECTDISTANCERANGE        41996

//--------------------------------------------------------------------------------
// GPS tags
//--------------------------------------------------------------------------------
#define QIMAGEMETADATA_GPS                         34853
#define QIMAGEMETADATA_GPSVERSIONID                    0
#define QIMAGEMETADATA_GPSLATITUDEREF                  1
#define QIMAGEMETADATA_GPSLATITUDE                     2
#define QIMAGEMETADATA_GPSLONGITUDEREF                 3
#define QIMAGEMETADATA_GPSLONGITUDE                    4
#define QIMAGEMETADATA_GPSALTITUDEREF                  5
#define QIMAGEMETADATA_GPSALTITUDE                     6
#define QIMAGEMETADATA_GPSTIMESTAMP                    7
#define QIMAGEMETADATA_GPSSATELLITES                   8
#define QIMAGEMETADATA_GPSSTATUS                       9
#define QIMAGEMETADATA_GPSMEASUREMODE                 10
#define QIMAGEMETADATA_GPSDOP                         11
#define QIMAGEMETADATA_GPSSPEEDREF                    12
#define QIMAGEMETADATA_GPSSPEED                       13
#define QIMAGEMETADATA_GPSTRACKREF                    14
#define QIMAGEMETADATA_GPSTRACK                       15
#define QIMAGEMETADATA_GPSIMGDIRECTIONREF             16
#define QIMAGEMETADATA_GPSIMGDIRECTION                17
#define QIMAGEMETADATA_GPSMAPDATUM                    18
#define QIMAGEMETADATA_GPSDESTLATITUDEREF             19
#define QIMAGEMETADATA_GPSDESTLATITUDE                20
#define QIMAGEMETADATA_GPSDESTLONGITUDEREF            21
#define QIMAGEMETADATA_GPSDESTLONGITUDE               22
#define QIMAGEMETADATA_GPSDESTBEARINGREF              23
#define QIMAGEMETADATA_GPSDESTBEARING                 24
#define QIMAGEMETADATA_GPSDESTDISTANCEREF             25
#define QIMAGEMETADATA_GPSDESTDISTANCE                26
#define QIMAGEMETADATA_GPSPROCESSINGMETHOD            27
#define QIMAGEMETADATA_GPSAREAINFORMATION             28
#define QIMAGEMETADATA_GPSDATESTAMP                   29
#define QIMAGEMETADATA_GPSDIFFERENTIAL                30

//--------------------------------------------------------------------------------
// XMP tags
//--------------------------------------------------------------------------------
#define QIMAGEMETADATA_XMP                           700

//--------------------------------------------------------------------------------
// Pseudo tags
//--------------------------------------------------------------------------------
#define QIMAGEMETADATA_LENS                        50000
#define QIMAGEMETADATA_SERIALNUMBER                50001

//--------------------------------------------------------------------------------
// Headers
//--------------------------------------------------------------------------------
#include <QtCore/QtGlobal>
#include <QtCore/QFile>
#include <QtCore/QDataStream>
#include <QtCore/QVector>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QIODevice>
#include <QtCore/QMap>
#include <QtCore/QVariant>

#include "QImageMetaDataRational.h"

/*!
 *The class delivers features for reading metadata of TIFF, JPEG, and PNG images.
 *
 * The class follows the TIFF, EXIF, and XMP standards unless otherwise
 * stated. The class supports TIFF, EXIF, and GPS entries.
 *
 * The documentation of the class can be generated with Doxygen.
 */
class QImageMetaData
{
  //------------------------------------------------------------------------------
  // Public
  //------------------------------------------------------------------------------
public:
  /*!
   * The enum defines the error codes.
   */
  enum ErrorCode {ErrorCodeUndefined,                    /*!< The error code has not been defined, i.e., no error has been occurred. */
                  ErrorCodeFileNotOpened,                /*!< The file or the io device could not be opened. */
                  ErrorCodeImageFormatNotIdentified,     /*!< The image format was not identified. */
                  ErrorCodeImageWidthEntryIllegal,       /*!< The value of the width entry is illegal, i.e., smaller or equal to zero. */
                  ErrorCodeImageHeightEntryIllegal,      /*!< The value of the height entry is illegal, i.e., smaller or equal to zero. */
                  ErrorCodePixelXDimensionEntryIllegal,  /*!< The value of the pixel x dimension entry is illegal, i.e., smaller or equal to zero. */
                  ErrorCodePixelYDimensionEntryIllegal,  /*!< The value of the pixel y dimension entry is illegal, i.e., smaller or equal to zero. */
                  ErrorCodeCellWidthEntryIllegal,        /*!< The value of the cell width entry is illegal, i.e., smaller or equal to zero. */
                  ErrorCodeCellLengthEntryIllegal,       /*!< The value of the cell length entry is illegal, i.e., smaller or equal to zero. */
                  ErrorCodeTileWidthEntryIllegal,        /*!< The value of the tile width entry is illegal, i.e., smaller or equal to zero. */
                  ErrorCodeTileLengthEntryIllegal,       /*!< The value of the tile length entry is illegal, i.e., smaller or equal to zero. */
                  ErrorCodePNGInvalidHeaderLength,       /*!< The length of the PNG header is invalid, i.e., inequal to 13 bytes. */
                  ErrorCodePNGInvalidHeaderType,         /*!< The type of the PNG header is invalid. */
                  ErrorCodePNGInvalidHeaderWidth,        /*!< The width entry of the PNG header is invalid. */
                  ErrorCodePNGInvalidHeaderHeight,       /*!< The height entry of the PNG header is invalid. */
                  ErrorCodePNGInvalidHeaderDepth,        /*!< The depth entry of the PNG header is invalid. */
                  ErrorCodePNGInvalidHeaderColourType,   /*!< The colour type entry of the PNG header is invalid. */
                  ErrorCodeWarningLimitExceeded,         /*!< The warning limit has been exceeded. */
                  ErrorCodeGPSLatitudeReferenceInvalid,  /*!< The reference of the latitude is invalid. */
                  ErrorCodeGPSLongitudeReferenceInvalid, /*!< The reference of the longitude is invalid. */
                  ErrorCodeGPSLatitudeInvalid,           /*!< The latitude is invalid. */
                  ErrorCodeGPSLongitudeInvalid           /*!< The longitude is invalid. */
                };

  /*!
   * The enum defines the compression methods.
   */
  enum Compression {CompressionUndefined,    /*!< Undefined */
                    CompressionUncompressed, /*!< Uncompressed */
                    CompressionCCIT1D,       /*!< CCIT 1D  */
                    CompressionGroup3Fax,    /*!< Group 3 Fax */
                    CompressionGroup4Fax,    /*!< Group 4 Fax */
                    CompressionLZW,          /*!< LZW */
                    CompressionJPEG,         /*!< JPEG */
                    CompressionPackBits,     /*!< Pack bits */
                    CompressionUnknown       /*!< Unknown */
                  };

  /*!
   * The enum defines the image formats.
   */
  enum ImageFormat {ImageFormatUndefined, /*!< Undefined */
                    ImageFormatTIFF,      /*!< TIFF */
                    ImageFormatJPEG,      /*!< JPEG */
                    ImageFormatPNG,       /*!< PNG */
                    ImageFormatUnknown    /*!< Unknown */
                  };

  /*!
   * The enum defines the photometric interpretations.
   */
  enum Photometric {PhotometricUndefined,        /*!< Undefined */
                    PhotometricWhiteIsZero,      /*!< White is zero */
                    PhotometricBlackIsZero,      /*!< Black is zero */
                    PhotometricRGB,              /*!< RGB */
                    PhotometricRGBPalette,       /*!< RGB palette */
                    PhotometricTransparencyMask, /*!< Transparency mask */
                    PhotometricCMYK,             /*!< CMYK */
                    PhotometricYCbCr,            /*!< YCbCr */
                    PhotometricCIELab,           /*!< CIE Lab */
                    PhotometricUnknown           /*!< Unknown */
                  };

  /*!
   * The enum defines the planar configurations.
   */
  enum PlanarConfiguration {PlanarUndefined, /*!< Undefined */
                            PlanarChunky,    /*!< Chunky */
                            PlanarPlanar,    /*!< Planar */
                            PlanarUnknown    /*!< Unknown */
                          };

  /*!
   * The enum defines the resolution units.
   */
  enum ResolutionUnit {ResolutionUndefined,  /*!< Undefined */
                       ResolutionNoUnit,     /*!< Not applicable */
                       ResolutionInch,       /*!< Inch */
                       ResolutionCentimeter, /*!< Centimeter */
                       ResolutionUnknown     /*!< Unknown */
                     };

  /*!
   * The enum defines the orientations.
   */
  enum Orientation {OrientationUndefined,   /*!< Undefined */
                    OrientationTopLeft,     /*!< Top left */
                    OrientationTopRight,    /*!< Top right */
                    OrientationBottomRight, /*!< Bottom right */
                    OrientationBottomLeft,  /*!< Bottom left */
                    OrientationLeftTop,     /*!< Left top */
                    OrientationRightTop,    /*!< Right top */
                    OrientationRightBottom, /*!< Right bottom */
                    OrientationLeftBottom,  /*!< Left bottom */
                    OrientationUnknown      /*!< Unknown */
                  };

  /*!
   * The enum defines the exposure programs.
   */
  enum ExposureProgram {ExposureProgramUndefined,        /*!< Undefined */
                        ExposureProgramNotDefined,       /*!< Not applicable */
                        ExposureProgramManual,           /*!< Manual */
                        ExposureProgramNormal,           /*!< Normal */
                        ExposureProgramAperturePriority, /*!< Aperture priority */
                        ExposureProgramShutterPriority,  /*!< Shutter priority */
                        ExposureProgramCreative,         /*!< Creative */
                        ExposureProgramAction,           /*!< Action */
                        ExposureProgramPortrait,         /*!< Portrait */
                        ExposureProgramLandscape,        /*!< Landscape */
                        ExposureProgramUnknown           /*!< Unknown */
                      };

  /*!
   * The enum defines the light sources.
   */
  enum LightSource {LightSourceUndefined,            /*!< Undefined */
                    LightSourceDaylight,             /*!< Daylight */
                    LightSourceFluorescent,          /*!< Fluorescent */
                    LightSourceTungsten,             /*!< Tungsten */
                    LightSourceFlash,                /*!< Flash */
                    LightSourceFineWeather,          /*!< Fine weather */
                    LightSourceCloudyWeather,        /*!< Cloudy weather */
                    LightSourceShade,                /*!< Shade */
                    LightSourceDaylightFluorescent,  /*!< Daylight fluorescent */
                    LightSourceDayWhiteFluorescent,  /*!< Day white fluorescent */
                    LightSourceCoolWhiteFluorescent, /*!< Cool white fluorescent */
                    LightSourceWhiteFluorescent,     /*!< White fluorescent */
                    LightSourceStandardLightA,       /*!< Standard light A */
                    LightSourceStandardLightB,       /*!< Standard light B */
                    LightSourceStandardLightC,       /*!< Standard light C */
                    LightSourceD55,                  /*!< D55 */
                    LightSourceD65,                  /*!< D65 */
                    LightSourceD75,                  /*!< D75 */
                    LightSourceD50,                  /*!< D50 */
                    LightSourceISOStudioTungsten,    /*!< ISO studio tungsten */
                    LightSourceOther,                /*!< Other */
                    LightSourceUnknown               /*!< Unknown */
                  };

  /*!
   * The enum defines the sensing methods.
   */
  enum SensingMethod {SensingMethodUndefined,                   /*!< Undefined */
                      SensingMethodNotDefined,                  /*!< Not applicable */
                      SensingMethodOneChipColorAreaSensor,      /*!< One chip color area sensor */
                      SensingMethodTwoChipColorAreaSensor,      /*!< Two chip color area sensor */
                      SensingMethodThreeChipColorAreaSensor,    /*!< Three chip color area sensor */
                      SensingMethodColorSequentialSensor,       /*!< Color sequential sensor */
                      SensingMethodTrilinearSensor,             /*!< Trilinear sensor */
                      SensingMethodColorSequentialLinearSensor, /*!< Color sequential linear sensor */
                      SensingMethodUnknown                      /*!< Unknown */
                    };

  /*!
   * The enum defines the exposure modes.
   */
  enum ExposureMode {ExposureModeUndefined,   /*!< Undefined */
                     ExposureModeAuto,        /*!< Auto */
                     ExposureModeManual,      /*!< Manual */
                     ExposureModeAutoBracket, /*!< Auto bracket*/
                     ExposureModeUnknown      /*!< Unknown */
                   };

  /*!
   * The enum defines the white balance modes.
   */
  enum WhiteBalance {WhiteBalanceUndefined, /*!< Undefined */
                     WhiteBalanceAuto,      /*!< Auto */
                     WhiteBalanceManual,    /*!< Manual */
                     WhiteBalanceUnknown    /*!< Unknown */
                   };

  /*!
   * The enum defines the gain control types.
   */
  enum GainControl {GainControlUndefined, /*!< Undefined */
                    GainControlNone,      /*!< None */
                    GainControlLowUp,     /*!< Low up */
                    GainControlHighUp,    /*!< High up */
                    GainControlLowDown,   /*!< Low down */
                    GainControlHighDown,  /*!< High down */
                    GainControlUnknown    /*!< Unknown */
                  };

  /*!
   * The enum defines the saturation types.
   */
  enum Saturation {SaturationUndefined, /*!< Undefined */
                   SaturationNormal,    /*!< Normal */
                   SaturationLow,       /*!< Low */
                   SaturationHigh,      /*!< High */
                   SaturationUnknown    /*!< Unknown */
                 };

  /*!
   * The enum defines the sharpness modes.
   */
  enum Sharpness {SharpnessUndefined, /*!< Undefined */
                  SharpnessNormal,    /*!< Normal */
                  SharpnessSoft,      /*!< Soft */
                  SharpnessHard,      /*!< Hard */
                  SharpnessUnknown    /*!< Unknown */
                };

  /*!
   * The enum defines the subject distance range types.
   */
  enum SubjectDistanceRange {SubjectDistanceRangeUndefined,    /*!< Undefined */
                             SubjectDistanceRangeMacro,        /*!< Macro */
                             SubjectDistanceRangeCloseView,    /*!< CLose view */
                             SubjectDistanceRangeDistanceView, /*!< Distance view */
                             SubjectDistanceRangeUnknown       /*!< Unknown */
                           };

  /*!
   * The enum defines the color spaces.
   */
  enum ColorSpace {ColorSpaceUndefined,    /*!< Undefined */
                   ColorSpacesRGB,         /*!< sRGB */
                   ColorSpaceUncalibrated, /*!< Uncalibrated */
                   ColorSpaceUnknown       /*!< Unknown */
                 };

  /*!
   * The enum defines the scene capture types.
   */
  enum SceneCaptureType {SceneCaptureTypeUndefined, /*!< Undefined */
                         SceneCaptureTypeStandard,  /*!< Standard */
                         SceneCaptureTypeLandscape, /*!< Landscape */
                         SceneCaptureTypePortrait,  /*!< Portrait */
                         SceneCaptureTypeNight,     /*!< Night */
                         SceneCaptureTypeUnknown    /*!< Unknown */
                       };

  /*!
   * The enum defines the contrast modes.
   */
  enum Contrast {ContrastUndefined, /*!< Undefined */
                 ContrastSoft,      /*!< Soft */
                 ContrastNormal,    /*!< Normal */
                 ContrastHard,      /*!< Hard */
                 ContrastUnknown    /*!< Unknown */
               };

  /*!
   * The enum defines the image processing modes.
   */
  enum CustomRendered {CustomRenderedUndefined, /*!< Undefined */
                       CustomRenderedNormal,    /*!< Normal */
                       CustomRenderedCustom,    /*!< Custom */
                       CustomRenderedUnknown    /*!< Unknown */
                     };

  /*!
   * The enum defines the YCbCr positioning modes.
   */
  enum YCbCrPositioning {YCbCrPositioningUndefined, /*!< Undefined */
                         YCbCrPositioningCentered,  /*!< Centered */
                         YCbCrPositioningCoSited,   /*!< Co-sited*/
                         YCbCrPositioningUnknown    /*!< Unknown */
                       };

  /*!
   * The enum defines the metering modes.
   */
  enum MeteringMode {MeteringModeUndefined,             /*!< Undefined */
                     MeteringModeAverage,               /*!< Average */
                     MeteringModeCenterWeightedAverage, /*!< Center weighted average */
                     MeteringModeSpot,                  /*!< Spot */
                     MeteringModeMultiSpot,             /*!< Multi-spot */
                     MeteringModePattern,               /*!< Pattern */
                     MeteringModePartial,               /*!< Partial */
                     MeteringModeUnknown                /*!< Unknown */
                   };

  /*!
   * The enum defines the flash status types.
   */
  enum FlashStatus {FlashStatusUndefined, /*!< Undefined */
                    FlashStatusNotFired,  /*!< Not fired */
                    FlashStatusFired,     /*!< Fired */
                    FlashStatusUnknown    /*!< Unknown */
                  };

  /*!
   * The enum defines the flash strobe types.
   */
  enum FlashStrobe {FlashStrobeUndefined,               /*!< Undefined */
                    FlashStrobeNoStrobeReturnDetection, /*!< No strobe return light detection */
                    FlashStrobeReturnLightNotDetected,  /*!< Strobe return light not detected */
                    FlashStrobeReturnLightDetected,     /*!< Strobe return light detected */
                    FlashStrobeUnknown                  /*!< Unknown */
                  };

  /*!
   * The enum defines the flash modes.
   */
  enum FlashMode {FlashModeUndefined,                  /*!< Undefined */
                  FlashModeCompulsoryFlashFiring,      /*!< Compulsory flash firing */
                  FlashModeCompulsoryFlashSuppression, /*!< Compulsory flash suppression */
                  FlashModeAuto,                       /*!< Auto */
                  FlashModeUnknown                     /*!< Unknown */
                };

  /*!
   * The enum defines the flash function types.
   */
  enum FlashFunction {FlashFunctionUndefined, /*!< Undefined */
                      FlashFunctionEnabled,   /*!< Enabled */
                      FlashFunctionDisabled,  /*!< Disabled */
                      FlashFunctionUnknown    /*!< Unknown */
                    };

  /*!
   * The enum defines the flash red-eye types.
   */
  enum FlashRedEye {FlashRedEyeUndefined, /*!< Undefined */
                    FlashRedEyeDisabled,  /*!< Disabled */
                    FlashRedEyeEnabled,   /*!< Enabled */
                    FlashRedEyeUnknown    /*!< Unknown */
                  };

  /*!
   * The enum defines the latitude reference types.
   */
  enum GPSLatitude {GPSLatitudeUndefined, /*!< Undefined */
                    GPSLatitudeNorth,     /*!< North */
                    GPSLatitudeSouth,     /*!< South */
                    GPSLatitudeUnknown    /*!< Unknown */
                  };

  /*!
   * The enum defines the longitude reference types.
   */
  enum GPSLongitude {GPSLongitudeUndefined, /*!< Undefined */
                     GPSLongitudeEast,      /*!< East */
                     GPSLongitudeWest,      /*!< West */
                     GPSLongitudeUnknown    /*!< Unknown */
                   };

  /*!
   * The enum defines the altitude reference types.
   */
  enum GPSAltitude {GPSAltitudeUndefined,     /*!< Undefined */
                    GPSAltitudeAboveSeaLevel, /*!< Above sea level */
                    GPSAltitudeBelowSeaLevel, /*!< Below sea level */
                    GPSAltitudeUnknown        /*!< Unknown */
                  };

  /*!
   * The enum defines the status types.
   */
  enum GPSStatus {GPSStatusUndefined,             /*!< Undefined */
                  GPSStatusMeasurementInProgress, /*!< Measurement in progress */
                  GPSStatusInteroperability,      /*!< Interoperability */
                  GPSStatusUnknown                /*!< Unknown */
                };

  /*!
   * The enum defines the measure modes.
   */
  enum GPSMeasureMode {GPSMeasureModeUndefined,        /*!< Undefined */
                       GPSMeasureModeTwoDimensional,   /*!< Two dimensional */
                       GPSMeasureModeThreeDimensional, /*!< Three dimensional */
                       GPSMeasureModeUnknown           /*!< Unknown */
                     };

  /*!
   * The enum defines the speed types.
   */
  enum GPSSpeed {GPSSpeedUndefined,  /*!< Undefined */
                 GPSSpeedKilometers, /*!< Kilometers per hour */
                 GPSSpeedMiles,      /*!< Miles per hour */
                 GPSSpeedKnots,      /*!< Knots */
                 GPSSpeedUnknown     /*!< Unknown */
               };

  /*!
   * The enum defines the direction types.
   */
  enum GPSDirection {GPSDirectionUndefined, /*!< Undefined */
                     GPSDirectionTrue,      /*!< True */
                     GPSDirectionMagnetic,  /*!< Magnetic */
                     GPSDirectionUnknown    /*!< Unknown */
                   };

  /*!
   * The enum defines the distance types.
   */
  enum GPSDistance {GPSDistanceUndefined,  /*!< Undefined */
                    GPSDistanceKilometers, /*!< Kilometers */
                    GPSDistanceMiles,      /*!< Miles */
                    GPSDistanceKnots,      /*!< Knots */
                    GPSDistanceUnknown     /*!< Unknown */
                  };

  /*!
   * The enum defines the differential types.
   */
  enum GPSDifferential {GPSDifferentialUndefined,         /*!< Undefined */
                        GPSDifferentialWithoutCorrection, /*!< Without correction */
                        GPSDifferentialWithCorrection,    /*!< With correction */
                        GPSDifferentialUnknown            /*!< Unknown */
                      };

  /*!
   * The enum defines the types.
   */
  enum PNGType {IHDR, /*!< Header */
                PLTE, /*!< Palette */
                IDAT, /*!< Data */
                IEND, /*!< End */
                bKGD, /*!< Default background color */
                cHRM, /*!< Chromaticities of primaries and white point */
                gAMA, /*!< Gamma */
                hIST, /*!< Histogram */
                iCCP, /*!< ICC color profile */
                iTXt, /*!< Text */
                pHYs, /*!< Aspect ratio */
                sBIT, /*!< Color accuracy */
                sPLT, /*!< Palette */
                sRGB, /*!< sRGB color space */
                tEXt, /*!< Text */
                tIME, /*!< Date and time */
                tRNS, /*!< Transparency */
                zTXt, /*!< Text */
                iVLd  /*!< Invalid, custom type which indicates that the type of the chunk cannot be determined */
              };

  /*!
   * The enum defines the types.
   */
  enum JPEGType {SOI,   /*!< Start of image */
                 SOF0,  /*!< Start of frame */
                 SOF1,  /*!< Start of frame */
                 SOF2,  /*!< Start of frame */
                 SOF3,  /*!< Start of frame */
                 SOF5,  /*!< Start of frame */
                 SOF6,  /*!< Start of frame */
                 SOF7,  /*!< Start of frame */
                 JPG,   /*!< JPEG extensions */
                 SOF9,  /*!< Start of frame */
                 SOF10, /*!< Start of frame */
                 SOF11, /*!< Start of frame */
                 SOF13, /*!< Start of frame */
                 SOF14, /*!< Start of frame */
                 SOF15, /*!< Start of frame */
                 DHT,   /*!< Huffman tables */
                 DAC,   /*!< Arithmetic coding conditions */
                 DQT,   /*!< Quantization tables */
                 DNL,   /*!< Number of lines */
                 DRI,   /*!< Restart interval */
                 DHP,   /*!< Hierarcial progression */
                 EXP,   /*!< Extensions for reference components */
                 SOS,   /*!< Start of scan */
                 RST0,  /*!< Restart */
                 RST1,  /*!< Restart */
                 RST2,  /*!< Restart */
                 RST3,  /*!< Restart */
                 RST4,  /*!< Restart */
                 RST5,  /*!< Restart */
                 RST6,  /*!< Restart */
                 RST7,  /*!< Restart */
                 APP0,  /*!< Application specific */
                 APP1,  /*!< Application specific */
                 APP2,  /*!< Application specific */
                 APP3,  /*!< Application specific */
                 APP4,  /*!< Application specific */
                 APP5,  /*!< Application specific */
                 APP6,  /*!< Application specific */
                 APP7,  /*!< Application specific */
                 APP8,  /*!< Application specific */
                 APP9,  /*!< Application specific */
                 APPA,  /*!< Application specific */
                 APPB,  /*!< Application specific */
                 APPC,  /*!< Application specific */
                 APPD,  /*!< Application specific */
                 APPE,  /*!< Application specific */
                 APPF,  /*!< Application specific */
                 JPG0,  /*!< JPEG extensions */
                 JPG1,  /*!< JPEG extensions */
                 JPG2,  /*!< JPEG extensions */
                 JPG3,  /*!< JPEG extensions */
                 JPG4,  /*!< JPEG extensions */
                 JPG5,  /*!< JPEG extensions */
                 JPG6,  /*!< JPEG extensions */
                 JPG7,  /*!< JPEG extensions */
                 JPG8,  /*!< JPEG extensions */
                 JPG9,  /*!< JPEG extensions */
                 JPGA,  /*!< JPEG extensions */
                 JPGB,  /*!< JPEG extensions */
                 JPGC,  /*!< JPEG extensions */
                 JPGD,  /*!< JPEG extensions */
                 JPGE,  /*!< JPEG extensions */
                 JPGF,  /*!< JPEG extensions */
                 COM,   /*!< Comment */
                 TEM,   /*!< For temporary private use in arithmetic coding */
                 EOI,   /*!< End of image */
                 IVL    /*!< Invalid, custom type which indicates that the type of the marker cannot be determined */
               };

  //------------------------------------------------------------------------------
  // Constructors and destructors
  //------------------------------------------------------------------------------

  /*!
   * The default constructor.
   */
  QImageMetaData();

  /*!
   * The default destructor.
   */
  ~QImageMetaData();

  /*!
   * The copy constructor.
   */
  QImageMetaData(const QImageMetaData& obj);

  /*!
   * The copy assignment operator.
   */
  QImageMetaData& operator=(const QImageMetaData& rhs);

  //------------------------------------------------------------------------------
  // Error code
  //------------------------------------------------------------------------------

  /*!
   * Returns the error code.
   *
   * \return The error code.
   */
  ErrorCode errorCode();

  //------------------------------------------------------------------------------
  // Read methods
  //------------------------------------------------------------------------------

  /*!
   * The method reads the metadata of the file.
   *
   * \param fileName The name of the file.
   *
   * \return True if the metadata was read successfully; false otherwise.
   */
  bool read(QString fileName);

  /*!
   * The method reads the metadata of the io device.
   *
   * \param data The io device.
   *
   * \return True if the metadata was read successfully; false otherwise.
   */
  bool read(QIODevice& data);

  //------------------------------------------------------------------------------
  // Auxiliary methods
  //------------------------------------------------------------------------------

  /*!
   * The method returns the list of the tags which have been defined.
   * The list includes only the TIFF and EXIF metadata.
   * The list does not include the XMP metadata.
   *
   * \return The list of the tags.
   */
  QVector<quint32> definedTags();

  /*!
   * The method returns the list of the tags which have not been supported.
   * The list includes only the TIFF and EXIF metadata.
   * The list does not include the XMP metadata.
   *
   * \return The list of the tags.
   */
  QVector<quint32> unsupportedTags();

  //------------------------------------------------------------------------------
  // Entry methods
  //------------------------------------------------------------------------------

  /*!
   * The method returns the image description.
   *
   * \return The image description.
   */
  QString imageDescription();

  /*!
   * The method returns the make.
   *
   * \return The make.
   */
  QString make();

  /*!
   * The method returns the model.
   *
   * \return The model.
   */
  QString model();

  /*!
   * The method returns the artist.
   *
   * \return The artist.
   */
  QString artist();

  /*!
   * The method returns the width.
   *
   * \sa pixelXDimension
   *
   * \return The width.
   */
  quint32 width();

  /*!
   * The method returns the height.
   *
   * \sa pixelYDimension
   *
   * \return The height.
   */
  quint32 height();

  /*!
   * The method returns the depth, i.e., the bits per sample.
   *
   * \return The depth.
   */
  QVector<quint32> depth();

  /*!
   * The method returns the exposure time.
   *
   * \sa shutterSpeed
   *
   * \return The exposure time.
   */
  QImageMetaDataRational<quint32> exposureTime();

  /*!
   * The method returns the shutter speed.
   *
   * \sa exposureTime
   *
   * \return The shutter speed.
   */
  QImageMetaDataRational<quint32> shutterSpeed();

  /*!
   * The method returns the aperture.
   *
   * \sa fNumber
   *
   * \return The aperture.
   */
  QImageMetaDataRational<quint32> aperture();

  /*!
   * The method returns the f-number.
   *
   * \sa aperture
   *
   * \return The f-number.
   */
  QImageMetaDataRational<quint32> fNumber();

  /*!
   * The method returns the focal length.
   *
   * \sa focalLength35mm
   *
   * \return The focal length.
   */
  QImageMetaDataRational<quint32> focalLength();

  /*!
   * The method returns the ISO speed ratings.
   *
   * \return The ISO speed ratings.
   */
  QVector<quint32> ISOSpeedRatings();

  /*!
   * The method returns the focal length in 35mm format.
   *
   * \sa focalLength
   *
   * \return The focal length.
   */
  quint32 focalLength35mm();

  /*!
   * The method returns the compression.
   *
   * \return The compression.
   */
  Compression compression();

  /*!
   * The method returns the photometric interpretation.
   *
   * \return The photometric interpretation.
   */
  Photometric photometricInterpretation();

  /*!
   * The method returns the number of samples.
   *
   * \return The number of samples.
   */
  quint32 samples();

  /*!
   * The method returns the x resolution.
   *
   * \return The x resolution.
   */
  qreal xResolution();

  /*!
   * The method returns the y resolution.
   *
   * \return The y resolution.
   */
  qreal yResolution();

  /*!
   * The method returns the planar configuration.
   *
   * \return The planar configuration.
   */
  PlanarConfiguration planarConfiguration();

  /*!
   * The method returns the resolution unit.
   *
   * \return The resolution unit.
   */
  ResolutionUnit resolutionUnit();

  /*!
   * The method returns the orientation.
   *
   * \return The orientation.
   */
  Orientation orientation();

  /*!
   * The method returns the .
   *
   * \return The .
   */
  QString software();

  /*!
   * The method returns the date and time.
   *
   * \return The date and time.
   */
  QString dateAndTime();

  /*!
   * The method returns the subseconds of the date and time.
   *
   * \return The subseconds.
   */
  QString dateAndTimeSubseconds();

  /*!
   * The method returns the date and time of the original version.
   *
   * \return The date and time.
   */
  QString dateAndTimeOriginal();

  /*!
   * The method returns the subseconds of the date and time of the original version.
   *
   * \return The subseconds.
   */
  QString dateAndTimeOriginalSubseconds();

  /*!
   * The method returns the date and time of the digitized version.
   *
   * \return The date and time.
   */
  QString dateAndTimeDigitized();

  /*!
   * The method returns the subseconds of the date and time of the digitized version.
   *
   * \return The subseconds.
   */
  QString dateAndTimeDigitizedSubseconds();

  /*!
   * The method returns the exposure program.
   *
   * \return The exposure program.
   */
  ExposureProgram exposureProgram();

  /*!
   * The method returns the light source.
   *
   * \return The light source.
   */
  LightSource lightSource();

  /*!
   * The method returns the flash entry.
   *
   * \return The entry.
   */
  quint32 flash();

  /*!
   * The method returns the status of the flash.
   *
   * \return The status of the flash.
   */
  FlashStatus flashStatus();

  /*!
   * The method returns the strobe return light mode of the flash.
   *
   * \return The strobe return light mode of the flash.
   */
  FlashStrobe flashStrobe();

  /*!
   * The method returns the mode of the flash.
   *
   * \return The mode of the flash.
   */
  FlashMode flashMode();

  /*!
   * The method returns the function of the flash.
   *
   * \return The function of the flash.
   */
  FlashFunction flashFunction();

  /*!
   * The method returns the red-eye reduction mode of the flash.
   *
   * \return The red-eye reduction mode of the flash.
   */
  FlashRedEye flashRedEye();

  /*!
   * The method returns the exposure bias.
   *
   * \return The exposure bias.
   */
  qreal exposureBias();

  /*!
   * The method returns the max aperture.
   *
   * \return The max aperture.
   */
  qreal maxAperture();

  /*!
   * The method returns the copyright.
   *
   * \return The copyright.
   */
  QString copyright();

  /*!
   * The method returns the color space.
   *
   * \return The color space.
   */
  ColorSpace colorSpace();

  /*!
   * The method returns the pixel x dimension.
   *
   * \sa width
   *
   * \return The pixel x dimension.
   */
  quint32 pixelXDimension();

  /*!
   * The method returns the pixel y dimension.
   *
   * \sa height
   *
   * \return The pixel y dimension.
   */
  quint32 pixelYDimension();

  /*!
   * The method returns the digital zoom ratio.
   *
   * \return The digital zoom ratio.
   */
  qreal digitalZoomRatio();

  /*!
   * The method returns the gain control.
   *
   * \return The gain control.
   */
  GainControl gainControl();

  /*!
   * The method returns the sensing method.
   *
   * \return The sensing method.
   */
  SensingMethod sensingMethod();

  /*!
   * The method returns the processing mode.
   *
   * \return The processing mode.
   */
  CustomRendered customRendered();

  /*!
   * The method returns the metering mode.
   *
   * \return The metering mode.
   */
  MeteringMode meteringMode();

  /*!
   * The method returns the exposure mode.
   *
   * \return The exposure mode.
   */
  ExposureMode exposureMode();

  /*!
   * The method returns the white balance.
   *
   * \return The white balance.
   */
  WhiteBalance whiteBalance();

  /*!
   * The method returns the scene capture type.
   *
   * \return The scene capture type.
   */
  SceneCaptureType sceneCaptureType();

  /*!
   * The method returns the contrast.
   *
   * \return The contrast.
   */
  Contrast contrast();

  /*!
   * The method returns the saturation.
   *
   * \return The saturation.
   */
  Saturation saturation();

  /*!
   * The method returns the sharpness.
   *
   * \return The sharpness.
   */
  Sharpness sharpness();

  /*!
   * The method returns the subject distance range.
   *
   * \return The subject distance range.
   */
  SubjectDistanceRange subjectDistanceRange();

  /*!
   * The method returns the yCbCr subsampling.
   *
   * \return The yCbCr subsampling.
   */
  QVector<quint32> yCbCrSubSampling();

  /*!
   * The method returns the yCbCr positioning.
   *
   * \return The yCbCr positioning.
   */
  YCbCrPositioning yCbCrPositioning();

  /*!
   * The method returns the brightness.
   *
   * \return The brightness.
   */
  qreal brightness();

  /*!
   * The method returns the focal plane x resolution.
   *
   * \return The focal plane x resolution.
   */
  qreal focalPlaneXResolution();

  /*!
   * The method returns the focal plane y resolution.
   *
   * \return The focal plane y resolution.
   */
  qreal focalPlaneYResolution();

  /*!
   * The method returns the focal plane resolution unit.
   *
   * \return The focal plane resolution unit.
   */
  ResolutionUnit focalPlaneResolutionUnit();

  /*!
   * The method returns the name of the document.
   *
   * \return The name of the document.
   */
  QString documentName();

  /*!
   * The method returns the name of the page.
   *
   * \return The name of the page.
   */
  QString pageName();

  /*!
   * The method returns the host computer.
   *
   * \return The host computer.
   */
  QString hostComputer();

  /*!
   * The method returns the number of rows  a strip.
   *
   * \return The number of rows a strip.
   */
  quint32 rowsPerStrip();

  /*!
   * The method returns the strip offsets.
   *
   * \return The strip offsets.
   */
  QVector<quint32> stripOffsets();

  /*!
   * The method returns the strip byte counts.
   *
   * \return The strip byte counts.
   */
  QVector<quint32> stripByteCounts();

  /*!
   * The method returns the cell width.
   *
   * \return The cell width.
   */
  quint32 cellWidth();

  /*!
   * The method returns the cell length.
   *
   * \return The cell length.
   */
  quint32 cellLength();

  /*!
   * The method returns the tile width.
   *
   * \return The tile width.
   */
  quint32 tileWidth();

  /*!
   * The method returns the tile length.
   *
   * \return The tile length.
   */
  quint32 tileLength();

  /*!
   * The method returns the tile offsets.
   *
   * \return The tile offsets.
   */
  QVector<quint32> tileOffsets();

  /*!
   * The method returns the tile byte counts.
   *
   * \return The tile byte counts.
   */
  QVector<quint32> tileByteCounts();

  /*!
   * The method returns the compressed bits per pixel.
   *
   * \return The compressed bits per pixel.
   */
  qreal compressedBitsPerPixel();

  /*!
   * The method returns the related sound file.
   *
   * \return The related sound file.
   */
  QString relatedSoundFile();

  /*!
   * The method returns the image identifier.
   *
   * \return The image identifier.
   */
  QString imageUniqueID();

  /*!
   * The method returns the thresholding value.
   *
   * \return The thresholding value.
   */
  quint32 thresholding();

  /*!
   * The method returns the fill order of bits.
   *
   * \return The fill order of bits.
   */
  quint32 fillOrder();

  /*!
   * The method returns the minimum sample value.
   *
   * \return The minimum sample value.
   */
  QVector<quint32> minSampleValue();

  /*!
   * The method returns the maximum sample value.
   *
   * \return The maximum sample value.
   */
  QVector<quint32> maxSampleValue();

  /*!
   * The method returns the x position.
   *
   * \return The x position.
   */
  QImageMetaDataRational<quint32> xPosition();

  /*!
   * The method returns the y position.
   *
   * \return The y position.
   */
  QImageMetaDataRational<quint32> yPosition();

  /*!
   * The method returns the offsets of unused bytes.
   *
   * \return The offsets of unused bytes.
   */
  QVector<quint32> freeOffsets();

  /*!
   * The method returns the number of unused bytes.
   *
   * \return The number of unused bytes.
   */
  QVector<quint32> freeByteCounts();

  /*!
   * The method returns the precision of the gray response curve.
   *
   * \sa grayResponseCurve
   *
   * \return The precision of the gray response curve.
   */
  quint32 grayResponseUnit();

  /*!
   * The method returns the gray response curve.
   *
   * \sa grayResponseUnit
   *
   * \return The gray response curve.
   */
  QVector<quint32> grayResponseCurve();

  /*!
   * The method returns the T4-encoding options.
   *
   * \sa T6Options
   *
   * \return The T4-encoding options.
   */
  quint32 T4Options();

  /*!
   * The method returns the T6-encoding options.
   *
   * \sa T4Options
   *
   * \return The T6-encoding options.
   */
  quint32 T6Options();

  /*!
   * The method returns the page number.
   *
   * \return The page number.
   */
  QVector<quint32> pageNumber();

  /*!
   * The method returns the transfer function.
   *
   * \return The transfer function.
   */
  QVector<quint32> transferFunction();

  /*!
   * The method returns the predictor.
   *
   * \return The predictor.
   */
  quint32 predictor();

  /*!
   * The method returns the white point.
   *
   * \return The white point.
   */
  QVector< QImageMetaDataRational<quint32> > whitePoint();

  /*!
   * The method returns the chromaticities of primaries.
   *
   * \return The chromaticities of primaries.
   */
  QVector< QImageMetaDataRational<quint32> > primaryChromaticities();

  /*!
   * The method returns the color map of a palette color image.
   *
   * \return The color map.
   */
  QVector<quint32> colorMap();

  /*!
   * The method returns the hafltone function.
   *
   * \return The halftone function.
   */
  QVector<quint32> halfToneHints();

  /*!
   * The method returns the spectral sensitivity.
   *
   * \return The spectral sensitivity.
   */
  QString spectralSensitivity();

  /*!
   * The method returns the subject distance.
   *
   * \return The subject distance.
   */
  QImageMetaDataRational<quint32> subjectDistance();

  /*!
   * The method returns the subject area.
   *
   * \return The subject area.
   */
  QVector<quint32> subjectArea();

  /*!
   * The method returns the flash energy.
   *
   * \return The flash energy.
   */
  QImageMetaDataRational<quint32> flashEnergy();

  /*!
   * The method returns the subject location.
   *
   * \return The subject location.
   */
  QVector<quint32> subjectLocation();

  /*!
   * The method returns the exposure index.
   *
   * \return The exposure index.
   */
  QImageMetaDataRational<quint32> exposureIndex();

  /*!
   * The method returns the set of inks.
   *
   * \return The set of inks.
   */
  quint32 inkSet();

  /*!
   * The method returns the names of inks.
   *
   * \return The names of inks.
   */
  QString inkNames();

  /*!
   * The method returns the number of inks.
   *
   * \return The number of inks.
   */
  quint32 numberOfInks();

  /*!
   * The method returns the dot range.
   *
   * \return The dot range.
   */
  QVector<quint32> dotRange();

  /*!
   * The method returns the target printer.
   *
   * \return The target printer.
   */
  QString targetPrinter();

  /*!
   * The method returns the additional components.
   *
   * \return The additional components.
   */
  QVector<quint32> extraSamples();

  /*!
   * The method returns the sample format.
   *
   * \return The sample format.
   */
  QVector<quint32> sampleFormat();

  /*!
   * The method returns the transfer range.
   *
   * \return The transfer range.
   */
  QVector<quint32> transferRange();

  /*!
   * The method returns the yCbCr coefficients.
   *
   * \return The yCbCr coefficients.
   */
  QVector< QImageMetaDataRational<quint32> > yCbCrCoefficients();

  /*!
   * The method returns the reference black and white.
   *
   * \return The reference black and white.
   */
  QVector< QImageMetaDataRational<quint32> > referenceBlackWhite();

  /*!
   * The method returns the exif version.
   *
   * \return The exif version.
   */
  QString exifVersion();

  /*!
   * The method returns the flashpix version.
   *
   * \return The flashpix version.
   */
  QString flashPixVersion();

  /*!
   * The method returns the components configuration.
   *
   * \return The components configuration.
   */
  QVector<quint32> componentsConfiguration();

  /*!
   * The method determines if the location can be defined.
   *
   * \return True if the location can be defined; false otherwise.
   */
  bool gpsLocation();

  /*!
   * The method returns the GPS version.
   *
   * \return The GPS version.
   */
  QVector<quint32> gpsVersion();

  /*!
   * The method returns the reference of the latitude.
   *
   * \sa gpsLatitude
   *
   * \return The reference of the latitude.
   */
  GPSLatitude gpsLatitudeRef();

  /*!
   * The method returns the latitude.
   *
   * \sa gpsLatitudeRef
   *
   * \return The latitude.
   */
  QVector< QImageMetaDataRational<quint32> > gpsLatitude();

  /*!
   * The method returns the degrees of the latitude.
   * If the latitude has not been defined or the latitude is invalid,
   * the method returns zero.
   *
   * \sa gpsLatitude
   *
   * \return The degrees of the latitude.
   */
  qreal gpsLatitudeDegrees();

  /*!
   * The method returns the minutes of the latitude.
   * If the latitude has not been defined or the latitude is invalid,
   * the method returns zero.
   *
   * \sa gpsLatitude
   *
   * \return The minutes of the latitude.
   */
  qreal gpsLatitudeMinutes();

  /*!
   * The method returns the seconds of the latitude.
   * If the latitude has not been defined or the latitude is invalid,
   * the method returns zero.
   *
   * \sa gpsLatitude
   *
   * \return The seconds of the latitude.
   */
  qreal gpsLatitudeSeconds();

  /*!
   * The method returns the reference of the longitude.
   *
   * \sa gpslongitude
   *
   * \return The reference of the longitude.
   */
  GPSLongitude gpsLongitudeRef();

  /*!
   * The method returns the longitude.
   *
   * \sa gpslongitudeRef
   *
   * \return The longitude.
   */
  QVector< QImageMetaDataRational<quint32> > gpsLongitude();

  /*!
   * The method returns the degrees of the longitude.
   * If the longitude has not been defined or the longitude is invalid,
   * the method returns zero.
   *
   * \sa gpsLongitude
   *
   * \return The degrees of the longitude.
   */
  qreal gpsLongitudeDegrees();

  /*!
   * The method returns the minutes of the longitude.
   * If the longitude has not been defined or the longitude is invalid,
   * the method returns zero.
   *
   * \sa gpsLongitude
   *
   * \return The minutes of the longitude.
   */
  qreal gpsLongitudeMinutes();

  /*!
   * The method returns the seconds of the longitude.
   * If the longitude has not been defined or the longitude is invalid,
   * the method returns zero.
   *
   * \sa gpsLongitude
   *
   * \return The seconds of the longitude.
   */
  qreal gpsLongitudeSeconds();

  /*!
   * The method returns the reference of the altitude.
   *
   * \sa gpsAltitude
   *
   * \return The reference of the altitude.
   */
  GPSAltitude gpsAltitudeRef();

  /*!
   * The method returns the altitude.
   *
   * \sa gpsAltitudeRef
   *
   * \return The altitude.
   */
  QImageMetaDataRational<quint32> gpsAltitude();

  /*!
   * The method returns the time stamp.
   *
   * \sa gpsDateStamp
   *
   * \return The time stamp.
   */
  QVector< QImageMetaDataRational<quint32> > gpsTimeStamp();

  /*!
   * The method returns the satellites.
   *
   * \return The satellites.
   */
  QString gpsSatellites();

  /*!
   * The method returns the status.
   *
   * \return The status.
   */
  GPSStatus gpsStatus();

  /*!
   * The method returns the measurement mode.
   *
   * \return The measurement mode.
   */
  GPSMeasureMode gpsMeasureMode();

  /*!
   * The method returns the measurement precision.
   *
   * \return The measurement precision.
   */
  QImageMetaDataRational<quint32> gpsDOP();

  /*!
   * The method returns the reference of the speed.
   *
   * \return The reference of the speed.
   */
 GPSSpeed gpsSpeedRef();

 /*!
  * The method returns the speed.
  *
  * \return The speed.
  */
  QImageMetaDataRational<quint32> gpsSpeed();

  /*!
   * The method returns the reference of the track.
   *
   * \return The reference of the track.
   */
  GPSDirection gpsTrackRef();

  /*!
   * The method returns the track.
   *
   * \return The track.
   */
  QImageMetaDataRational<quint32> gpsTrack();

  /*!
   * The method returns the reference of the direction.
   *
   * \return The reference of the direction.
   */
  GPSDirection gpsImgDirectionRef();

  /*!
   * The method returns the direction.
   *
   * \return The direction.
   */
  QImageMetaDataRational<quint32> gpsImgDirection();

  /*!
   * The method returns the geodetic survey data.
   *
   * \return The geodetic survey data.
   */
  QString gpsMapDatum();

  /*!
   * The method returns the reference of the latitude of the destination.
   *
   * \return The reference of the latitude.
   */
  GPSLatitude gpsDestLatitudeRef();

  /*!
   * The method returns the latitude of the destination.
   *
   * \return The latitude.
   */
  QVector< QImageMetaDataRational<quint32> > gpsDestLatitude();

  /*!
   * The method returns the reference of the longitude of the destination.
   *
   * \return The reference of the longitude.
   */
  GPSLongitude gpsDestLongitudeRef();

  /*!
   * The method returns the longitude of the destination.
   *
   * \return The longitude.
   */
  QVector< QImageMetaDataRational<quint32> > gpsDestLongitude();

  /*!
   * The method returns the reference of the bearing of the destination.
   *
   * \return The reference of the bearing.
   */
  GPSDirection gpsDestBearingRef();

  /*!
   * The method returns the bearing of the destination.
   *
   * \return The bearing.
   */
  QImageMetaDataRational<quint32> gpsDestBearing();

  /*!
   * The method returns the reference of the distance of the destination.
   *
   * \return The reference of the distance.
   */
  GPSDistance gpsDestDistanceRef();

  /*!
   * The method returns the distance of the destination.
   *
   * \return The distance.
   */
  QImageMetaDataRational<quint32> gpsDestDistance();

  /*!
   * The method returns the date stamp.
   *
   * \sa gpsTimeStamp
   *
   * \return The date stamp.
   */
  QString gpsDateStamp();

  /*!
   * The method returns the differential mode.
   *
   * \return The differential mode.
   */
  quint32 gpsDifferential();

  /*!
   * The method returns the lens information.
   *
   * \return The lens information.
   */
  QString lens();

  /*!
   * The method returns the serial number.
   *
   * \return The serial number.
   */
  QString serialNumber();

  /*!
   * The method returns the error message.
   *
   * \return The error message.
   */
  QString errorMessage();

  /*!
   * The method defines the warning limit of the parser.
   * By default, the warning limit is equal to ten warnings.
   *
   * \param limit the warning limit.
   */
  void warningLimit(quint32 limit);

//--------------------------------------------------------------------------------
// Protected
//--------------------------------------------------------------------------------
protected:
  /*!
   * The method identifies the image format.
   *
   * \param data The io device.
   *
   * \return True if the image format was identified successfully; false otherwise.
   */
  bool identify(QIODevice& data);

  /*!
   * The method reads the header of a PNG image.
   *
   * \param data The io device.
   *
   * \return True if the header was read successfully; false otherwise.
   */
  bool readPNGHeader(QIODevice& data);

  /*!
   * The method determines the type of a PNG chunk.
   * If the type cannot be determined, the type is set to invalid.
   *
   * \param type The value of the chunk.
   *
   * \return The type of the PNG chunk.
   */
  PNGType determinePNGType(quint32 type);

  /*!
   * The method finds the text chunks of a PNG image.
   *
   * \param data The io device.
   */
  void findPNGTextChunks(QIODevice& data);

  /*!
   * The method reads the text chunks of a PNG image.
   *
   * \param data The io device.
   */
  void readPNGTextChunks(QIODevice& data);

  /*!
   * The method determines the type of a JPEG marker.
   * If the type of the marker cannot be determined, the type is set to invalid.
   *
   * \param value The value of the JPEG marker.
   *
   * \return The type of the JPEG marker.
   */
  JPEGType determineJPEGType(quint16 value);

  /*!
   * The method reads an IFD from the io device.
   *
   * \param data The io device.
   * \param position The position of the IFD in the io device.
   */
  void readIFD(QIODevice& data,quint32 position);

  /*!
   * The method reads the XMP metadata.
   *
   * \param xmp The XMP metadata.
   */
  void readXMP(QString xmp);

  /*!
   * The method reads an XML entry.
   *
   * \param xml The XML stream.
   * \param text The text of the XML entry.
   * \param name The name of the XML entry.
   *
   * \return True if the XML entry was read successfully; false otherwise.
   */
  bool readXMPEntry(QXmlStreamReader &xml,QString name,QString &text);

  /*!
   * The method reads the text of an XML entry and saves it to a string.
   *
   * \param xml The XML stream.
   * \param name The name of the XML entry.
   * \param entry The text of the XML entry.
   */
  void readXMPString(QXmlStreamReader &xml,QString name,QString &entry);

  /*!
   * The method reads the text of an XML entry and converts the it to an unsigned integer.
   *
   * \param xml The XML stream.
   * \param name The name of the XML entry.
   * \param entry The value of the XML entry.
   */
  void readXMPString(QXmlStreamReader &xml,QString name,quint32 &entry);

  /*!
   * The method reads the array of text of an XML entry and converts it to an array of unsigned integers.
   *
   * \param xml The XML stream.
   * \param name The name of the XML entry.
   * \param entry The array of unsigned integers of the XML entry.
   */
  void readXMPStringArray(QXmlStreamReader &xml,QString name,QVector<quint32> &entry);

  /*!
   * The method reads the text of an XML entry and converts it to an unsigned rational.
   *
   * \param xml The XML stream.
   * \param name The name of the XML entry.
   * \param rational The unsigned rational of the XML entry.
   */
  void readXMPRationalUnsigned(QXmlStreamReader &xml,QString name,QImageMetaDataRational<quint32> &rational);

  /*!
   * The method reads the array of text of an XML entry and converts it to an array of unsigned rationals.
   *
   * \param xml The XML stream.
   * \param name The name of the XML entry.
   * \param rational The array of unsigned rationals of the XML entry.
   */
  void readXMPRationalUnsignedArray(QXmlStreamReader &xml,QString name,QVector< QImageMetaDataRational<quint32> > &rational);

  /*!
   * The method reads the text of an XML entry and converts it to a signed rational.
   *
   * \param xml The XML stream.
   * \param name The name of the XML entry.
   * \param rational The signed rational of the XML entry.
   */
  void readXMPRationalSigned(QXmlStreamReader &xml,QString name,QImageMetaDataRational<qint32> &rational);

  /*!
   * The method reads an XML entry to a string.
   * The method return a boolean which indicates if the XML entry was read successfully.
   * The method is required for XML entries which are based on enumerated types.
   *
   * \param xml The XML stream.
   * \param name The name of the XML entry.
   * \param entry The string of the XML entry.
   *
   * \return True if the XML entry was read successfully; false otherwise.
   */
  bool readXMPType(QXmlStreamReader &xml,QString name,QString &entry);

  /*!
   * The method reads an XML entry to the string which is converted to an unsigned integer.
   * The method return a boolean which indicates if the XML entry was read and converted successfully.
   * The method is required for XML entries which are based on enumerated types.
   *
   * \param xml The XML stream.
   * \param name The name of the XML entry.
   * \param entry The value of the XML entry.
   *
   * \return True if the XML entry was read successfully; false otherwise.
   */
  bool readXMPType(QXmlStreamReader &xml,QString name,quint32 &entry);

  /*!
   * The method reads the array of text of an XML entry.
   *
   * \param xml The XML stream.
   * \param text The array of text of the XML entry.
   * \param name The name of the XML entry.
   *
   * \return True if the array of text was read successfully; false otherwise.
   */
  bool readXMPStringArray(QXmlStreamReader &xml,QVector<QString> &text,QString name);

  /*!
   * The method converts a string to an unsigned integer,
   * but maintains the original unsigned integer if the conversion fails.
   *
   * \param text The string.
   * \param value The original unsigned integer.
   *
   * \return The unsigned integer.
   */
  quint32 convertToUint(quint32 value,QString text);

  /*!
   * The method converts a string to an unsigned integer,
   * but maintains the original unsigned integer if the conversion fails.
   *
   * \param text The text.
   * \param value The original unsigned integer.
   *
   * \return True if the conversion was successful; false otherwise.
   */
  bool convertToUint(QString text,quint32 &value);

  /*!
   * The method converts an array of strings to an array of unsigned integers,
   * but maintains the original array of unsigned integers if any of the conversions fails.
   *
   * \param text The array of strings.
   * \param value The array of original unsigned integers.
   *
   * \return The array of unsigned integers.
   */
  QVector<quint32> convertToUint(QVector<quint32> value,QVector<QString> text);

  /*!
   * The method compares the name of an XML entry to the keyword.
   * The method is case insensitive.
   *
   * \param keyword - The keyword.
   * \param name - The name of an XML entry.
   *
   * \return True if the name of the XML entry matches the keyword; false otherwise.
   */
  bool compareName(QString keyword,QString name);

  /*!
   * The method converts the text of an XML entry to an unsigned rational.
   * If the conversion fails, the original unsigned rational is not modified.
   *
   * \param text - The text.
   * \param rational - The unsigned rational.
   */
  void setUnsignedRational(QString text,QImageMetaDataRational<quint32> &rational);

  /*!
   * The method converts the text of an XML entry to an array of unsigned rationals.
   * If any of the conversion fails, the method return the original array of unsigned rationals
   *
   * \param text - The text.
   * \param rationalArray - The original array of unsigned rationals.
   *
   * \return The array of unsigned rationals.
   */
  QVector<  QImageMetaDataRational<quint32> > setUnsignedRational(QVector<QString> text,QVector< QImageMetaDataRational<quint32> > &rationalArray);

  /*!
   * The method converts the text of an XML entry to a signed rational.
   * If the conversion fails, the original signed rational is not modified.
   *
   * \param text - The text.
   * \param rational - The signed rational.
   */
  void setSignedRational(QString text,QImageMetaDataRational<qint32> &rational);

  /*!
   * The method converts the text of an XML entry to an array of signed rationals.
   * If any of the conversion fails, the method return the original array of signed rationals
   *
   * \param text - The text.
   * \param rationalArray - The original array of signed rationals.
   *
   * \return The array of signed rationals.
   */
  QVector<  QImageMetaDataRational<qint32> > setSignedRational(QVector<QString> text,QVector< QImageMetaDataRational<qint32> > &rationalArray);

  /*!
   * The method reads an unsigned rational from the io device.
   *
   * \param data The io device.
   * \param offset The position of the unsigned rational.
   *
   * \return The unsigned rational.
   */
  QImageMetaDataRational<quint32> readRational(QIODevice& data,quint32 offset);

  /*!
   * The method reads a signed rational from the io device.
   *
   * \param data The io device.
   * \param offset The position of the signed rational.
   *
   * \return The signed rational.
   */
  QImageMetaDataRational<qint32> readSRational(QIODevice& data,quint32 offset);

  /*!
   * The method reads an array of unsigned rationals from the io device.
   *
   * \param data The io device.
   * \param count The count of the array.
   * \param offset The position of the array.
   *
   * \return The array of unsigned rationals.
   */
  QVector< QImageMetaDataRational<quint32> > readRationalArray(QIODevice& data,quint32 count,quint32 offset);

  /*!
   * The method reads an array of signed rationals from the io device.
   *
   * \param data The io device.
   * \param count The count of the array.
   * \param offset The position of the array.
   *
   * \return The array of signed rationals.
   */
  QVector< QImageMetaDataRational<qint32> > readSRationalArray(QIODevice& data,quint32 count,quint32 offset);

  /*!
   * The method reads an array of unsigned integers from the io device.
   *
   * \param data The io device.
   * \param type The type of the array.
   * \param count The count of the array.
   * \param offset The position of the array.
   *
   * \return The array of unsigned integers.
   */
  QVector<quint32> readArray(QIODevice& data,quint32 type,quint32 count,quint32 offset);

  /*!
   * The method reads a string from the io device.
   *
   * \param data The io device.
   * \param count The count of the string.
   * \param offset The position of the string.
   *
   * \return The string.
   */
  QString readString(QIODevice& data,quint32 count,quint32 offset);

  /*!
   * The method computes the byte count of a value.
   *
   * \param type The type of the value.
   * \param count The count of the value.
   *
   * \return The byte count of the value.
   */
  quint32 byteCount(quint16 type,quint32 count);

  /*!
   * The method determines if a value is left-justitified, i.e., the length of the value is less than four bytes.
   *
   * \param type The type of the value.
   * \param count The count of the value.
   *
   * \return True if the value is left-justified; false otherwise.
   */
  bool leftJustified(quint16 type,quint32 count);

  /*!
   * The method verifies type, count, and value of an entry.
   *
   * \param tag - The tag of the entry.
   * \param type - The type of the entry.
   * \param count - The count of the entry.
   * \param value - The value of the entry.
   *
   * \return True if the entry is valid; false otherwise.
   */
  bool verifyEntry(quint16 tag,quint16 type,quint32 count,quint32 value);

  /*!
   * The method reads a left-justified value, which length is than four bytes, of an entry.
   *
   * \param data The io device.
   * \param type The type of the value.
   *
   * \return The value.
   */
  quint32 justify(QIODevice& data,quint32 type);

  /*!
   * The method defines the limit of the length of strings.
   * By default, the limit is equal to 2^16 - 1.
   *
   * \param limit The limit.
   */
  void stringLimit(quint32 limit);

  /*!
   * The method defines the limit of the length of generic values.
   * By default, the limit is equal to 2^16 - 1.
   *
   * \param limit The limit.
   */
  void genericLimit(quint32 limit);

  /*!
   * The method determines if the type of an entry is unsigned, i.e, byte, short, or long.
   *
   * \param type The value of the type.
   *
   * \return True is the type is unsigned; false otherwise.
   */
  bool type_unsigned(quint32 type);

  /*!
   * The method determines the type of the orientation.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the orientation.
   */
  Orientation orientationType(quint32 value);

  /*!
   * The method determines the type of the compression.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the compression.
   */
  Compression compressionType(quint32 value);

  /*!
   * The method determines the type of the photometric interpretation.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the photometric interpretation.
   */
  Photometric photometricInterpretationType(quint32 value);

  /*!
   * The method determines the type of the planar configuration.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the planar configuration.
   */
  PlanarConfiguration planarConfigurationType(quint32 value);

  /*!
   * The method determines the type of the resolution unit.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the resolution unit.
   */
  ResolutionUnit resolutionUnitType(quint32 value);

  /*!
   * The method determines the type of the YCbCr positioning.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the YCbCr positioning.
   */
  YCbCrPositioning yCbCrPositioningType(quint32 value);

  /*!
   * The method determines the type of the exposure program.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the exposure program.
   */
  ExposureProgram exposureProgramType(quint32 value);

  /*!
   * The method determines the type of the metering mode.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the metering mode.
   */
  MeteringMode meteringModeType(quint32 value);

  /*!
   * The method determines the type of the light source.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the light source.
   */
  LightSource lightSourceType(quint32 value);

  /*!
   * The method determines the type of the sensing method.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the sensing method.
   */
  SensingMethod sensingMethodType(quint32 value);

  /*!
   * The method determines the type of the image processing method.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the image processing method.
   */
  CustomRendered customRenderedType(quint32 value);

  /*!
   * The method determines the type of the exposure mode.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the exposure mode.
   */
  ExposureMode exposureModeType(quint32 value);

  /*!
   * The method determines the type of the white balance.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the white balance.
   */
  WhiteBalance whiteBalanceType(quint32 value);

  /*!
   * The method determines the type of the scene capture type.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the scene capture type.
   */
  SceneCaptureType sceneCaptureType(quint32 value);

  /*!
   * The method determines the type of the gain control.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the gain control.
   */
  GainControl gainControlType(quint32 value);

  /*!
   * The method determines the type of the contrast.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the contrast.
   */
  Contrast contrastType(quint32 value);

  /*!
   * The method determines the type of the saturation.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the saturation.
   */
  Saturation saturationType(quint32 value);

  /*!
   * The method determines the type of the sharpness.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the sharpness.
   */
  Sharpness sharpnessType(quint32 value);

  /*!
   * The method determines the type of the subject distance range.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the subject distance range.
   */
  SubjectDistanceRange subjectDistanceRangeType(quint32 value);

  /*!
   * The method determines the type of the color space.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the color space.
   */
  ColorSpace colorSpaceType(quint32 value);

  /*!
   * The method determines the type of the status of the flash.
   *
   * \return The type of the type of the status of the flash.
   */
  FlashStatus flashStatusType();

  /*!
   * The method determines the type of the strobe of the flast.
   *
   * \return The type of the strobe of the flash.
   */
  FlashStrobe flashStrobeType();

  /*!
   * The method determines the type of the mode of the flash.
   *
   * \return The type of the mode of the flash.
   */
  FlashMode flashModeType();

  /*!
   * The method determines the type of the function of the flash.
   *
   * \return The type of the function of the flash.
   */
  FlashFunction flashFunctionType();

  /*!
   * The method determines the type of the red-eye of the flash.
   *
   * \return The type of the red-eye of the flash.
   */
  FlashRedEye flashRedEeyeType();

  /*!
   * The method determines the type of the latitude.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the latitude.
   */
  GPSLatitude GPSLatitudeType(QString value);

  /*!
   * The method determines the type of the longitude.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the longitude.
   */
  GPSLongitude GPSLongitudeType(QString value);

  /*!
   * The method determines the type of the altitude.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the altitude.
   */
  GPSAltitude GPSAltitudeType(quint32 value);

  /*!
   * The method determines the type of the status.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the status.
   */
  GPSStatus GPSStatusType(QString value);

  /*!
   * The method determines the type of the measure mode.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the measure mode.
   */
  GPSMeasureMode GPSMeasureModeType(QString value);

  /*!
   * The method determines the type of the speed.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the speed.
   */
  GPSSpeed GPSSpeedType(QString value);

  /*!
   * The method determines the type of the direction.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the direction.
   */
  GPSDirection GPSDirectionType(QString value);

  /*!
   * The method determines the type of the distance.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the distance.
   */
  GPSDistance GPSDistanceType(QString value);

  /*!
   * The method determines the type of the differential mode.
   *
   * \param value The value read from the io device.
   *
   * \return The type of the differential mode.
   */
  GPSDifferential GPSDifferentialType(quint32 value);

  /*!
   * The method displays the name and the text of the XMP metadata entry with qDebug() method.
   * The method is for debugging purposes only.
   */
  void debugXMP();

  /*!
   * The method displays the XMP metadata with qDebug() method.
   * The method is for debugging purposes only.
   *
   * \param data The io device.
   * \param count The number of bytes of the XMP metadata.
   * \param position The position of the XMP metadata in the io device.
   */
  void displayXMP(QIODevice& data,quint32 count,quint32 position);

  /*!
   * The method defines the tag value for the name of the entry.
   * The purpose of the method to help to avoid long if-else loops.
   * If tag has not been defined, the method returns null.
   *
   * \param name The name of the entry.
   *
   * \return The tag value.
   */
  unsigned int defineTag(QString name);

//--------------------------------------------------------------------------------
// Private
//--------------------------------------------------------------------------------
private:
  //------------------------------------------------------------------------------
  // Error code and message
  //------------------------------------------------------------------------------
  ErrorCode errorCode_;

  QString errorMessage_;

  //------------------------------------------------------------------------------
  // TIFF
  //------------------------------------------------------------------------------
  bool tiffValid_;

  quint32 tiffOffset_;

  //------------------------------------------------------------------------------
  // Warning count and limit
  //------------------------------------------------------------------------------
  quint32 warningCount_;
  quint32 warningLimit_;

  //------------------------------------------------------------------------------
  // Base offset
  //------------------------------------------------------------------------------
  qint64 baseOffset_;

  //------------------------------------------------------------------------------
  // Image format
  //------------------------------------------------------------------------------
  ImageFormat imageFormat_;

  QDataStream::ByteOrder endianness_;

  //------------------------------------------------------------------------------
  // Defined tags
  //------------------------------------------------------------------------------
  QVector<quint32> definedTags_;

  //------------------------------------------------------------------------------
  // Unsupported tags
  //------------------------------------------------------------------------------
  QVector<quint32> unsupportedTags_;

  //------------------------------------------------------------------------------
  // Limits
  //------------------------------------------------------------------------------
  quint32 stringLimit_;
  quint32 genericLimit_;

  //------------------------------------------------------------------------------
  // iTXt chunks
  //------------------------------------------------------------------------------
  QVector<quint32> iTXtChunks_;
  QVector<quint32> iTXtSizes_;

  //------------------------------------------------------------------------------
  // TIFF tags
  //------------------------------------------------------------------------------
  quint32 width_;
  quint32 length_;

  QVector<quint32> depth_;

  Compression compression_;

  Photometric photometric_;

  quint32 thresholding_;

  quint32 cellWidth_;
  quint32 cellLength_;

  quint32 fillOrder_;

  QString documentName_;
  QString imageDescription_;
  QString make_;
  QString model_;

  QVector<quint32> stripOffsets_;

  Orientation orientation_;

  quint32 samples_;

  quint32 rowsPerStrip_;

  QVector<quint32> stripByteCounts_;

  QVector<quint32> minSampleValue_;
  QVector<quint32> maxSampleValue_;

  QImageMetaDataRational<quint32> xResolution_;
  QImageMetaDataRational<quint32> yResolution_;

  PlanarConfiguration planar_;

  QString pageName_;

  QImageMetaDataRational<quint32> xPosition_;
  QImageMetaDataRational<quint32> yPosition_;

  QVector<quint32> freeOffsets_;
  QVector<quint32> freeByteCounts_;

  quint32 grayResponseUnit_;

  QVector<quint32> grayResponseCurve_;

  quint32 T4Options_;
  quint32 T6Options_;

  ResolutionUnit resolution_;

  QVector<quint32> pageNumber_;

  QVector<quint32> transferFunction_;

  QString software_;
  QString artist_;
  QString dateAndTime_;
  QString hostComputer_;

  quint32 predictor_;

  QVector< QImageMetaDataRational<quint32> > whitePoint_;
  QVector< QImageMetaDataRational<quint32> > primaryChromaticities_;

  QVector<quint32> colorMap_;
  QVector<quint32> halfToneHints_;

  quint32 tileWidth_;
  quint32 tileLength_;

  QVector<quint32> tileOffsets_;
  QVector<quint32> tileByteCounts_;

  quint32 inkSet_;

  QString inkNames_;

  quint32 numberOfInks_;

  QVector<quint32> dotRange_;

  QString targetPrinter_;

  QVector<quint32> extraSamples_;

  QVector<quint32> sampleFormat_;

  QVector<quint32> transferRange_;

  QVector< QImageMetaDataRational<quint32> > yCbCrCoefficients_;

  QVector< QImageMetaDataRational<quint32> > referenceBlackWhite_;

  QVector<quint32> yCbCrSubSampling_;

  YCbCrPositioning yCbCrPositioning_;

  QString copyright_;

  //------------------------------------------------------------------------------
  // EXIF tags
  //------------------------------------------------------------------------------
  QString exifVersion_;
  QString flashPixVersion_;

  QVector<quint32> componentsConfiguration_;

  QImageMetaDataRational<quint32> exposureTime_;
  QImageMetaDataRational<quint32> fNumber_;

  ExposureProgram exposureProgram_;

  QString spectralSensitivity_;

  QVector<quint32> ISOSpeedRatings_;

  QString dateAndTimeOriginal_;
  QString dateAndTimeDigitized_;

  QImageMetaDataRational<quint32> compressedBitsPerPixel_;

  QImageMetaDataRational<quint32> shutterSpeed_;
  QImageMetaDataRational<quint32> aperture_;

  QImageMetaDataRational<qint32> brightness_;
  QImageMetaDataRational<qint32> exposureBias_;

  QImageMetaDataRational<quint32> maxAperture_;
  QImageMetaDataRational<quint32> subjectDistance_;

  MeteringMode meteringMode_;

  LightSource lightSource_;

  quint32 flash_;

  FlashStatus   flashStatus_;
  FlashStrobe   flashStrobe_;
  FlashMode     flashMode_;
  FlashFunction flashFunction_;
  FlashRedEye   flashRedEye_;

  QImageMetaDataRational<quint32> focalLength_;

  QVector<quint32> subjectArea_;

  QString dateAndTimeSubseconds_;
  QString dateAndTimeOriginalSubseconds_;
  QString dateAndTimeDigitizedSubseconds_;

  ColorSpace colorSpace_;

  quint32 pixelXDimension_;
  quint32 pixelYDimension_;

  QString relatedSoundFile_;

  QImageMetaDataRational<quint32> flashEnergy_;

  QImageMetaDataRational<quint32> focalPlaneXResolution_;
  QImageMetaDataRational<quint32> focalPlaneYResolution_;

  ResolutionUnit focalPlaneResolution_;

  QVector<quint32> subjectLocation_;

  QImageMetaDataRational<quint32> exposureIndex_;

  SensingMethod sensingMethod_;

  CustomRendered customRendered_;

  ExposureMode exposureMode_;

  WhiteBalance whiteBalance_;

  QImageMetaDataRational<quint32> digitalZoomRatio_;

  quint32 focalLength35mm_;

  SceneCaptureType sceneCaptureType_;

  GainControl gainControl_;

  Contrast contrast_;

  Saturation saturation_;

  Sharpness sharpness_;

  SubjectDistanceRange subjectDistanceRange_;

  QString imageUniqueID_;

  //------------------------------------------------------------------------------
  // GPS tags
  //------------------------------------------------------------------------------
  QVector<quint32> gpsVersion_;

  GPSLatitude  gpsLatitudeRef_;
  GPSLongitude gpsLongitudeRef_;

  GPSAltitude gpsAltitudeRef_;

  QVector< QImageMetaDataRational<quint32> > gpsLatitude_;
  QVector< QImageMetaDataRational<quint32> > gpsLongitude_;

  QImageMetaDataRational<quint32> gpsAltitude_;

  QVector< QImageMetaDataRational<quint32> > gpsTimeStamp_;

  QString gpsSatellites_;

  GPSStatus      gpsStatus_;
  GPSMeasureMode gpsMeasureMode_;

  QImageMetaDataRational<quint32> gpsDOP_;

  GPSSpeed     gpsSpeedRef_;
  GPSDirection gpsTrackRef_;

  QImageMetaDataRational<quint32> gpsSpeed_;
  QImageMetaDataRational<quint32> gpsTrack_;

  GPSDirection gpsImgDirectionRef_;

  QImageMetaDataRational<quint32> gpsImgDirection_;

  QString gpsMapDatum_;

  GPSLatitude  gpsDestLatitudeRef_;
  GPSLongitude gpsDestLongitudeRef_;
  GPSDirection gpsDestBearingRef_;
  GPSDistance  gpsDestDistanceRef_;

  QVector< QImageMetaDataRational<quint32> > gpsDestLatitude_;
  QVector< QImageMetaDataRational<quint32> > gpsDestLongitude_;
  QImageMetaDataRational<quint32> gpsDestBearing_;
  QImageMetaDataRational<quint32> gpsDestDistance_;

  QString gpsDateStamp_;

  GPSDifferential gpsDifferential_;

  //------------------------------------------------------------------------------
  // XMP tags
  //------------------------------------------------------------------------------
  QString lens_;
  QString serialNumber_;

  //------------------------------------------------------------------------------
  // XMP metadata debugging information
  //------------------------------------------------------------------------------
  QString debugXMPName_;
  QString debugXMPText_;
};

#endif
