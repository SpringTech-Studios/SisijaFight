#include <extensions/IProgressbar.h>

IProgressBar::IProgressBar(IGUIEnvironment* guienv, const core::rect<s32>& rectangle, s32 id, IGUIElement* parent) : IGUIElement(EGUIET_ELEMENT, guienv, parent, id, rectangle)
{
	total = rectangle.LowerRightCorner.X - rectangle.UpperLeftCorner.X;
	gui = guienv;
	bar = rectangle;

	if (parent == 0)
		guienv->getRootGUIElement()->addChild(this); //Ensure that draw method is called
	vdriver = this->gui->getVideoDriver();
	fillcolor.set(255, 255, 255, 255);
	emptycolor.set(255, 0, 0, 0);
	border = bar;
	this->setProgress(0);
}
void IProgressBar::setColors(irr::video::SColor progress, irr::video::SColor filling)
{
	fillcolor = progress;
	emptycolor = filling;
}
void IProgressBar::addBorder(irr::s32 size, irr::video::SColor color)
{
	bordercolor = color;
	border = bar;
	border.UpperLeftCorner.X -= size;
	border.UpperLeftCorner.Y -= size;
	border.LowerRightCorner.X += size;
	border.LowerRightCorner.Y += size;
}
void IProgressBar::setText(wchar_t* text) {
	Text = text;
}
void IProgressBar::setProgress(irr::u32 progress)
{
	if (progress > 100)
		progress = 0;

	u32 xpercentage;
	xpercentage = (progress * total) / 100; //Reducing to the bar size
	tofill.UpperLeftCorner.set(bar.UpperLeftCorner.X, bar.UpperLeftCorner.Y);
	tofill.LowerRightCorner.set(bar.UpperLeftCorner.X + xpercentage, bar.LowerRightCorner.Y);
	empty.UpperLeftCorner.set(tofill.LowerRightCorner.X, tofill.UpperLeftCorner.Y);
	empty.LowerRightCorner.set(bar.LowerRightCorner.X, bar.LowerRightCorner.Y);
}
void IProgressBar::draw()
{
	if (this->IsVisible == false)
		return;
	gui->getSkin()->getFont()->draw(Text, tofill, bordercolor, true, true);
	vdriver->draw2DRectangle(bordercolor, border);
	vdriver->draw2DRectangle(fillcolor, tofill);
	vdriver->draw2DRectangle(emptycolor, empty);
}