using System;
using System.IO;
using System.Linq;
using System.Text.Json;

// Read-only export: the CLI is called without --output, preserving game.droid.
EnsureDataLoaded();
var output = Environment.GetEnvironmentVariable("PCR_AUDIT_OUTPUT");
if (String.IsNullOrEmpty(output)) throw new Exception("PCR_AUDIT_OUTPUT is required");
var report = new {
    project = Data.GeneralInfo.Name.Content,
    yyc = Data.IsYYC(),
    bytecode_version = Data.GeneralInfo.BytecodeVersion,
    code_entry_count = Data.Code == null ? (int?)null : Data.Code.Count,
    scripts = Data.Scripts.Select(s => s.Name.Content).ToArray(),
    objects = Data.GameObjects.Select(o => new {
        name = o.Name.Content,
        sprite = o.Sprite == null ? null : o.Sprite.Name.Content,
        visible = o.Visible,
        persistent = o.Persistent,
        depth = o.Depth,
        parent = o.ParentId == null ? null : o.ParentId.Name.Content
    }).ToArray(),
    rooms = Data.Rooms.Select(r => new {
        name = r.Name.Content,
        width = r.Width, height = r.Height, speed = r.Speed,
        persistent = r.Persistent,
        instances = r.GameObjects.Select(i => new {
            id = i.InstanceID, x = i.X, y = i.Y,
            object_name = i.ObjectDefinition == null ? null : i.ObjectDefinition.Name.Content
        }).ToArray()
    }).ToArray(),
    limitations = new [] {
        "Resource structure only; compiled YYC functions are not reconstructed.",
        "Room instance positions do not establish runtime creation order or behavior."
    }
};
File.WriteAllText(output, JsonSerializer.Serialize(report, new JsonSerializerOptions { WriteIndented = true }));
Console.WriteLine("Read-only structure exported to " + output);
