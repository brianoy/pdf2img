// 網路圖形72 好一點100~200 不超過300
#define OUTPUT_DPI 72

#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>
#include <poppler/cpp/poppler-page-renderer.h>
#include <poppler/cpp/poppler-image.h>
#include <cairo/cairo.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <windows.h>

namespace fs = std::filesystem;
using namespace poppler; 

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
    double dpi = OUTPUT_DPI;

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
    if (argc < 2) {
        std::cerr << "Please drag a PDF file to this EXE." << std::endl;
        return 1;
    }

    // 將命令列參數轉換為 UTF-8
    std::string pdf_path = argv[1];
    
    std::cout << "pdf_path: " << pdf_path << std::endl;
    
    fs::path pdf_file(pdf_path);
    if (!fs::exists(pdf_file) || pdf_file.extension() != ".pdf") {
        std::cerr << "PDF file not found or invalid extension." << std::endl;
        return 1;
    }

    std::string base_name = pdf_file.stem().string();
    fs::path output_dir = pdf_file.parent_path() / base_name;
    std::cout << "output_dir " << output_dir << std::endl;
    std::cout << "base_name " << base_name << std::endl;
    fs::create_directory(output_dir);

    auto doc = document::load_from_file(pdf_path);
    if (!doc) {
        std::cerr << "Failed to open PDF file." << std::endl;
        return 1;
    }

    std::cout << "output_dir " << output_dir << std::endl;
    std::cout << "base_name " << base_name << std::endl;
    render_page_to_png(doc, output_dir, base_name);
    delete doc;

    std::cout << "Conversion completed. Output directory: " << output_dir << std::endl;
    return 0;
}