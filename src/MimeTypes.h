#pragma once
#include <string>
#include <unordered_map>

// extension => {mime_type:isText}
const std::unordered_map<std::string, std::pair<const char*, bool>> MimeTypes{
    {".htm", {"text/html", true}},
    {".html", {"text/html", true}},
    {".md", {"text/html", true}},
    {".php", {"text/html", true}},
    {".css", {"text/css", true}},
    {".txt", {"text/plain", true}},
    {".js", {"application/javascript", true}},
    {".json", {"application/json", true}},
    {".xml", {"application/xml", true}},
    {".swf", {"application/x-shockwave-flash", false}},
    {".wasm", {"application/wasm", false}},
    {".flv", {"video/x-flv", false}},
    {".png", {"image/png", false}},
    {".jpe", {"image/jpeg", false}},
    {".jpeg", {"image/jpeg", false}},
    {".jpg", {"image/jpeg", false}},
    {".gif", {"image/gif", false}},
    {".bmp", {"image/bmp", false}},
    {".ico", {"image/vnd.microsoft.icon", false}},
    {".tiff", {"image/tiff", false}},
    {".tif", {"image/tiff", false}},
    {".svg", {"image/svg+xml", false}},
    {".svgz", {"image/svg+xml", false}}};
