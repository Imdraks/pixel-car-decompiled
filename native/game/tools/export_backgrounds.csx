using System;
using System.IO;
using System.Linq;
using System.Text.Json;
EnsureDataLoaded();
var items = Data.Backgrounds.Where(b => b.Texture != null).Select(b => new {
    name = b.Name.Content,
    texture_id = Data.EmbeddedTextures.IndexOf(b.Texture.TexturePage),
    x = b.Texture.SourceX, y = b.Texture.SourceY,
    w = b.Texture.SourceWidth, h = b.Texture.SourceHeight,
    dx = b.Texture.TargetX, dy = b.Texture.TargetY,
    width = b.Texture.BoundingWidth, height = b.Texture.BoundingHeight
}).ToArray();
File.WriteAllText(Environment.GetEnvironmentVariable("PCR_BACKGROUND_OUTPUT"),
    JsonSerializer.Serialize(items, new JsonSerializerOptions { WriteIndented = true }));
Console.WriteLine("Exported " + items.Length + " backgrounds without modifying game.droid");
