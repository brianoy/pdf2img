#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>
#include <poppler/cpp/poppler-page-renderer.h>
#include <poppler/cpp/poppler-image.h>
#include <cairo/cairo.h>
#include <filesystem>
#include <iostream>
#include <string>

using namespace poppler;
namespace fs = std::filesystem;

void render_page_to_png(poppler::document* doc, const std::filesystem::path& output_dir, const std::string& base_name) {
    int num_pages = doc->pages();
    
    // 創建頁面渲染器
    page_renderer renderer;
    
    // 設置渲染提示
    renderer.set_render_hint(page_renderer::antialiasing, true);
    renderer.set_render_hint(page_renderer::text_antialiasing, true);
    renderer.set_render_hint(page_renderer::text_hinting, true);
    
    // 設置圖像格式為 RGB24
    renderer.set_image_format(image::format_rgb24);
    
    // 設置解析度為 300 DPI
    double dpi = 300.0;

    for (int i = 0; i < num_pages; ++i) {
        std::unique_ptr<poppler::page> p(doc->create_page(i));
        if (p) {
            // 渲染頁面
            image img = renderer.render_page(p.get(), dpi, dpi);
            
            if (img.is_valid()) {
                std::filesystem::path output_file = output_dir / (base_name + "_" + std::to_string(i) + ".png");
                img.save(output_file.string(), "png", static_cast<int>(dpi));
            }
        }
    }
}


int main(int argc, char* argv[]) {
    auto doc = document::load_from_file("123.pdf");
    if (doc) {
        render_page_to_png(doc, "", "");
        delete doc;
    }

}
