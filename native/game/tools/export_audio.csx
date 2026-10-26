using System;
using System.IO;
using System.Linq;
using System.Text.Json;
using System.Collections.Generic;
using System.Security.Cryptography;
EnsureDataLoaded();
string output=Environment.GetEnvironmentVariable("PCR_AUDIO_OUTPUT");
string source=Environment.GetEnvironmentVariable("PCR_AUDIO_SOURCE");
if(String.IsNullOrEmpty(output)||String.IsNullOrEmpty(source))throw new Exception("Set PCR_AUDIO_OUTPUT and PCR_AUDIO_SOURCE");
Directory.CreateDirectory(output);
var rows=new List<object>();
for(int i=0;i<Data.Sounds.Count;i++){
 var sound=Data.Sounds[i];string name=sound.Name.Content;
 string original=Path.Combine(source,sound.File.Content);
 if(sound.AudioFile==null&&!File.Exists(original))original=Directory.EnumerateFiles(source).Single(p=>String.Equals(Path.GetFileName(p),sound.File.Content,StringComparison.OrdinalIgnoreCase));
 byte[] bytes=sound.AudioFile!=null?sound.AudioFile.Data:File.ReadAllBytes(original);
 string ext=bytes.Length>4&&bytes[0]==(byte)'O'&&bytes[1]==(byte)'g'?".ogg":bytes.Length>4&&bytes[0]==(byte)'R'&&bytes[1]==(byte)'I'?".wav":Path.GetExtension(sound.File.Content);
 string file=name+ext;File.WriteAllBytes(Path.Combine(output,file),bytes);
 rows.Add(new {id=i,name,file,embedded=sound.AudioFile!=null,sha256=Convert.ToHexString(SHA256.HashData(bytes)).ToLowerInvariant(),size=bytes.Length,volume=sound.Volume,pitch=sound.Pitch});
}
File.WriteAllText(Path.Combine(output,"sounds.json"),JsonSerializer.Serialize(rows,new JsonSerializerOptions{WriteIndented=true}));
Console.WriteLine("Exported "+rows.Count+" original sounds without modifying game.droid");
