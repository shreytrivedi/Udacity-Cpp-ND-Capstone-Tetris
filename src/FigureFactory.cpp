#include "FigureFactory.h"

FigureFactory::FigureFactory(int typesOfFigures)
    : engine(dev())
    , figureSampleSpace(0, typesOfFigures-1)
{

}

std::unique_ptr<BaseFigure> FigureFactory::GetNextFigure(ITetrisHost *host)
{
    int figType = figureSampleSpace(engine);

    switch(figType)
    {
        case 0:
            return std::make_unique<FigureT>(host);
        case 1:
            return std::make_unique<FigureI>(host);
        case 2:
            return std::make_unique<FigureS>(host);
        case 3:
            return std::make_unique<FigureO>(host);
        case 4:
            return std::make_unique<FigureZ>(host);
        case 5:
            return std::make_unique<FigureL>(host);
        case 6:
            return std::make_unique<FigureJ>(host);
        
    }
}