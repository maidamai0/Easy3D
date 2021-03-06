#version 330   // for geometry shader to work
// please send comments or report bug to: liangliang.nan@gmail.com

in  vec3 vtx_position;  // point position
in  vec2 vtx_texcoord;  // texture coordinate
in  vec3 vtx_normal;    // point normal

uniform mat4 MANIP = mat4(1.0);
uniform mat3 NORMAL = mat3(1.0);

out VertexData
{
    vec2  texcoord;
    vec3  normal;
} vertexOut;


void main()
{
    vec4 new_position = MANIP * vec4(vtx_position, 1.0);

    gl_Position = new_position;

    vertexOut.texcoord = vtx_texcoord;
    vertexOut.normal = NORMAL * vtx_normal;
}
