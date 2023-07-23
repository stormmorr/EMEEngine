//****************************************************************************//
// corematerial.h                                                             //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_COREMATERIAL_H
#define CAL_COREMATERIAL_H


#include "cal3d/global.h"
#include "cal3d/refcounted.h"
#include "cal3d/refptr.h"


class CAL3D_API QunCoreMaterial : public cal3d::RefCounted
{
public:
  struct Color
  {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
  };

  struct Map
  {
    std::string strFilename;
    Qun::UserData userData;
  };

  QunCoreMaterial();
  QunCoreMaterial( const QunCoreMaterial& inOther );

protected:
  ~QunCoreMaterial() { }

public:
  Color& getAmbientColor();
  Color& getDiffuseColor();
  int getMapCount() const;
  const std::string& getMapFilename(int mapId) const;
  Qun::UserData getMapUserData(int mapId);
  float getShininess() const;
  Color& getSpecularColor();
  Qun::UserData getUserData();
  std::vector<Map>& getVectorMap();
  bool reserve(int mapCount);
  void setAmbientColor(const Color& ambientColor);
  void setDiffuseColor(const Color& diffuseColor);
  bool setMap(int mapId, const Map& map);
  bool setMapUserData(int mapId, Qun::UserData userData);
  void setShininess(float shininess);
  void setSpecularColor(const Color& specularColor);
  void setFilename(const std::string& filename);
  const std::string& getFilename(void) const;
  void setName(const std::string& name);
  const std::string& getName(void) const;
  void setUserData(Qun::UserData userData);

private:
  Color m_ambientColor;
  Color m_diffuseColor;
  Color m_specularColor;
  float m_shininess;
  std::vector<Map> m_vectorMap;
  Qun::UserData m_userData;
  std::string m_name;
  std::string m_filename;
};
typedef cal3d::RefPtr<QunCoreMaterial> QunCoreMaterialPtr;

#endif

//****************************************************************************//
