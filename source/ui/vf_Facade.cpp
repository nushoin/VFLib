// Copyright (C) 2008-2011 by Vincent Falco, All rights reserved worldwide.
// This file is released under the MIT License:
// http://www.opensource.org/licenses/mit-license.php

#include "vf/vf_StandardHeader.h"

BEGIN_VF_NAMESPACE

#include "vf/ui/vf_Control.h"
#include "vf/ui/vf_Facade.h"

namespace Ui {

namespace Facade {

const BorderSize <int> Base::fullyOpaque =
  BorderSize <int> (0, 0, 0, 0);

const BorderSize <int> Base::fullyTransparent =
  BorderSize <int> (TransparentBorder::maxBorderSize);

Base::Base()
  : m_control (nullptr)
  , m_model (nullptr)
  , m_isEnabled (true)
{
}

Base::~Base()
{
}

Model::Base& Base::getModel ()
{
  vfassert (m_model != nullptr);
  return *m_model;
}

Control::Base& Base::getControl ()
{
  vfassert (m_control != nullptr);
  return *m_control;
}

Component& Base::getComponent ()
{
  return getControl().getComponent();
}

Rectangle <int> Base::getLocalBounds ()
{
  return getComponent().getLocalBounds();
}

void Base::paintFacade (Graphics& g)
{
  paint (g);
}

void Base::paint (Graphics& g)
{
  paint(g, getControl().getComponent().getLocalBounds());
}

void Base::paintOverChildren (Graphics& g)
{
  paintOverChildren (g, getControl().getComponent().getLocalBounds());
}

bool Base::isEnabled()
{
  return m_isEnabled;
}

void Base::setEnabled (bool isEnabled)
{
  m_isEnabled = isEnabled;
}

BorderSize<int> Base::getTransparency()
{
  return fullyTransparent;
}

void Base::paint (Graphics& g, const Rectangle<int>& bounds)
{
}

void Base::paintOverChildren (Graphics& g, const Rectangle<int>& bounds)
{
}

void Base::attach (Model::Base* model, Control::Base* control)
{
  vfassert (m_control == nullptr && m_model == nullptr);

  m_model = model;
  m_control = control;

  onAttach ();
}

void Base::onAttach ()
{
  m_transparentBorder.setComponent (&getComponent(),
                                    getTransparency());
}

Path Base::createFittedRoundRect (const Rectangle<int>& bounds,
                                      float frameThickness,
                                      float cornerRadius)
{
  Path path;
  path.addRoundedRectangle(
    bounds.getX() + frameThickness/2,
    bounds.getY() + frameThickness/2,
    bounds.getWidth() - frameThickness,
    bounds.getHeight() - frameThickness,
    cornerRadius);
  return path;
}

//------------------------------------------------------------------------------

Empty::Empty()
{
}

BorderSize<int> Empty::getTransparency()
{
  return fullyTransparent;
}

void Empty::paint (Graphics& g, const Rectangle<int>& bounds)
{
  // nothing
}

}

}

END_VF_NAMESPACE