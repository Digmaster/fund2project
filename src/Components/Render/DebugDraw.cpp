#include "Components/Render/DebugDraw.h"
#include "Options.h"

DebugDraw::DebugDraw(sf::RenderWindow& app)
{
        std::cout << "New Debug Draw" << std::endl;
        this->window = &app;

        if(!defaultFont.loadFromFile("assets/Inconsolata.otf")){
            std::cout << "Failed to load Font" << std::endl;
        }
        //windowHeight = window->getSize().y; //Use to convert SFML y-axis to Box2D coordinates
        PPM = atoi(Options::instance().get("pixels_per_meter").c_str());
}

//convert a Box2D (float 0.0f - 1.0f range) color to a SFML color (uint8 0 - 255 range)
sf::Color DebugDraw::B2SFColor(const b2Color &color, int alpha = 255)
{
	sf::Color result((sf::Uint8)(color.r*255), (sf::Uint8)(color.g*255), (sf::Uint8)(color.b*255), (sf::Uint8) alpha);
	return result;
}

void DebugDraw::DrawAABB(b2AABB* aabb, const b2Color& color)
{
	sf::ConvexShape polygon;
	sf::Vector2f polygonVec[4];
	polygonVec[0] = {aabb->lowerBound.x*PPM, aabb->lowerBound.y*PPM};
	polygonVec[1] = {aabb->upperBound.x*PPM, aabb->lowerBound.y*PPM};
	polygonVec[2] = {aabb->upperBound.x*PPM, aabb->upperBound.y*PPM};
	polygonVec[3] = {aabb->lowerBound.x*PPM, aabb->upperBound.y*PPM};

	polygon.setPointCount(4);
	polygon.setPoint(0, polygonVec[0]);
	polygon.setPoint(1, polygonVec[1]);
	polygon.setPoint(2, polygonVec[2]);
	polygon.setPoint(3, polygonVec[3]);

    polygon.setOutlineThickness(1.0f);
    polygon.setFillColor(sf::Color::Red);
    polygon.setOutlineColor(sf::Color::Blue);
    //polygon.setOutlineColor(this->B2SFColor(color, 255));

	this->window->draw(polygon);
}


void DebugDraw::DrawString(int x, int y, const char* string)
{
    sf::Text fpsText;
    fpsText.setFont(defaultFont);
    fpsText.setCharacterSize(15);
    fpsText.setPosition(x,-y);
    fpsText.setString(string);
    this->window->draw(fpsText);
}

void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
        sf::CircleShape circle(1);
    circle.setPosition(p.x*PPM, -p.y*PPM);
    circle.setFillColor(this->B2SFColor(color, 50));
    circle.setOutlineThickness(1.0f);
    circle.setOutlineColor(this->B2SFColor(color));
    this->window->draw(circle);
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{
    float lineSize, lineProportion;
    lineProportion = 0.15; // 0.15 ~ 10 pixels
    b2Vec2 p1 = xf.p, p2;

	//red (X axis)
	p2 = p1 + (lineProportion * xf.q.GetXAxis());
	sf::Vertex redLine[]=
	{
    sf::Vertex(sf::Vector2f(p1.x*PPM, -p1.y*PPM), sf::Color::Red),
    sf::Vertex(sf::Vector2f(p2.x*PPM, -p2.y*PPM), sf::Color::Red)
};



	//green (Y axis)
	p2 = p1 - (lineProportion * xf.q.GetYAxis());
    sf::Vertex greenLine[]=
    {
        sf::Vertex(sf::Vector2f(p1.x*PPM, -p1.y*PPM), sf::Color::Green),
        sf::Vertex(sf::Vector2f(p2.x*PPM, -p2.y*PPM), sf::Color::Green)
    };

    this->window->draw(redLine, 1, sf::Lines);
    this->window->draw(greenLine, 1, sf::Lines);
}
void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    sf::Vertex line[]=
    {
      sf::Vertex(sf::Vector2f(p1.x*PPM, -p1.y*PPM), this->B2SFColor(color)),
      sf::Vertex(sf::Vector2f(p2.x*PPM, -p2.y*PPM), this->B2SFColor(color))

    };

   this->window->draw(line, 2, sf::Lines);
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    //no converion in cordinates of center and upper left corner, Circle in sfml is managed by default with the center
    sf::CircleShape circle(radius*PPM);
    circle.setPosition(center.x*PPM, center.y*PPM);
    circle.setFillColor(this->B2SFColor(color, 50));
    circle.setOutlineThickness(1.0f);
    circle.setOutlineColor(this->B2SFColor(color));

    b2Vec2 p = center + (radius * axis);
    sf::Vertex line[]=
    {
      sf::Vertex(sf::Vector2f(center.x*PPM, -center.y*PPM), this->B2SFColor(color)),
      sf::Vertex(sf::Vector2f(p.x*PPM, -p.y*PPM), this->B2SFColor(color))

    };

    this->window->draw(circle);
    this->window->draw(line, 2, sf::Lines);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    sf::CircleShape circle(radius*PPM);
    circle.setPosition(center.x*PPM, -center.y*PPM);
    circle.setOutlineThickness(1.0f);
    circle.setOutlineColor(this->B2SFColor(color));

    this->window->draw(circle);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    sf::ConvexShape polygon;
    sf::Vector2f polygonVec[vertexCount];
    polygon.setPointCount(vertexCount);

	for (int32 i=0; i<vertexCount; i++)
	{
		polygonVec[i] = {vertices[i].x*PPM, -vertices[i].y*PPM};
		polygon.setPoint(i,polygonVec[i]);
	}

	polygon.setOutlineThickness(1.0f);
	polygon.setFillColor(this->B2SFColor(color, 50));
	polygon.setOutlineColor(this->B2SFColor(color));


    //rendEng->addSprite(&polygon);
	this->window->draw(polygon);
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    sf::ConvexShape polygon;
    sf::Vector2f polygonVec[vertexCount];
    polygon.setPointCount(vertexCount);

	for (int32 i=0; i<vertexCount; i++)
	{
		polygonVec[i] = {vertices[i].x*PPM, -vertices[i].y*PPM};
		polygon.setPoint(i,polygonVec[i]);
	}

	polygon.setOutlineThickness(1.0f);
	polygon.setFillColor(sf::Color::Transparent);
	polygon.setOutlineColor(this->B2SFColor(color));

	//rendEng->addSprite(&polygon);
	this->window->draw(polygon);
}


void DebugDraw::DrawMouseJoint(b2Vec2& p1, b2Vec2& p2, const b2Color &boxColor, const b2Color &lineColor)
{
    sf::ConvexShape polygon;
    sf::ConvexShape polygon2;
    float p1x = p1.x * PPM;
    float p1y = p1.y * PPM;
    float p2x = p2.x * PPM;
    float p2y = p2.y * PPM;
    float size = 4.0f;

    sf::Color boxClr = this->B2SFColor(boxColor);
    sf::Color lineClr = this->B2SFColor(lineColor);

    sf::Vector2f polygonVec[4];
	polygonVec[0] = {p1x-size/2, p1y-size/2};
	polygonVec[1] = {p1x+size/2, p1y-size/2};
	polygonVec[2] = {p1x+size/2, p1y+size/2};
	polygonVec[3] = {p1x-size/2, p1y+size/2};

	sf::Vector2f polygon2Vec[4];
	polygon2Vec[0] = {p2x-size/2, p2y-size/2};
	polygon2Vec[1] = {p2x+size/2, p2y-size/2};
	polygon2Vec[2] = {p2x+size/2, p2y+size/2};
	polygon2Vec[3] = {p2x-size/2, p2y+size/2};


    for(int i = 0; i < 4; i++){
        //first green box for the joint
        polygon.setPoint(i, polygonVec[i]);

        //second green box for the joint
        polygon2.setPoint(i, polygon2Vec[i]);
    }

    sf::Vertex line[]=
    {
      sf::Vertex(sf::Vector2f(p1x, p1y), lineClr),
      sf::Vertex(sf::Vector2f(p2x, p2y), lineClr)

    };
    polygon.setFillColor(boxClr);
    polygon2.setFillColor(boxClr);

    this->window->draw(polygon);
    this->window->draw(polygon2);
    this->window->draw(line, 2, sf::Lines);
}

