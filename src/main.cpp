#include <thorvg.h>
#include <SDL2/SDL_image.h>

#include <iostream>

int main(int argc, const char** argv)
{
  const int WIDTH = 800, HEIGHT = 600;

  const char* output_filename = "result.png";
  if(argc == 2)
  {
    output_filename = argv[1];
  }

  std::unique_ptr< SDL_Surface, decltype(&SDL_FreeSurface) > surface(
    SDL_CreateRGBSurfaceWithFormat(0, WIDTH, HEIGHT, 32, SDL_PIXELFORMAT_ARGB8888),
    SDL_FreeSurface
  );

  if(!surface)
  {
    std::cerr << "failed to create surface" << std::endl;
    return 1;
  }

  tvg::Initializer::init(tvg::CanvasEngine::Sw, 0);
  // Generate a canvas
  auto canvas = tvg::SwCanvas::gen();
  // Setup the canvas target
  canvas->target(reinterpret_cast<uint32_t*>(surface->pixels), WIDTH, WIDTH, HEIGHT, tvg::SwCanvas::ARGB8888);

  auto rect = tvg::Shape::gen();
  // Append a rounded rectangle to the shape (x, y, w, h, rx, ry)
  rect->appendRect(50, 50, 200, 200, 20, 20);
  // Set the shape's color to (r, g, b)
  rect->fill(100, 100, 100);
  // Push the shape into the canvas
  canvas->push(std::move(rect));

  canvas->draw();
  canvas->sync();

  if(IMG_SavePNG(surface.get(), output_filename))
  {
    std::cerr << "failed to save image" << std::endl;
    return 1;
  }
  std::cout << "wrote to " << output_filename << std::endl;

  return 0;
}
