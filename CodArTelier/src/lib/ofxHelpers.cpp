#include "ofxHelpers.h"

string GenDateFileName()
{
  ostringstream ss;
  ss << std::setfill('0') << std::setw(2) << ofGetYear();
  ss << std::setfill('0') << std::setw(2) << ofGetMonth();
  ss << std::setfill('0') << std::setw(2) << ofGetDay();
  ss << "_";
  ss << std::setfill('0') << std::setw(2) << ofGetHours();
  ss << std::setfill('0') << std::setw(2) << ofGetMinutes();
  ss << std::setfill('0') << std::setw(2) << ofGetSeconds();
  return ss.str();
}

string GenDateFileName( string postfix)
{
  ostringstream ss;
  ss << GenDateFileName();
  ss << "_" << postfix;
  return ss.str();
}

void SaveFbo( const ofFbo& fbo, string filename)
{
  if (!fbo.isAllocated()) return;

  ofImage img;
  ofPixels pixels;

  fbo.readToPixels(pixels);
  img.setFromPixels(pixels);

  if(img.save(filename, ofImageQualityType::OF_IMAGE_QUALITY_BEST))
    ofLog() << "Fbo saved to " << filename << "\n";
  else
    ofLog() << "Faile to save Fbo to " << filename << "!\n";
}
