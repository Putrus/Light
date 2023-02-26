uniform vec2 lightPos;
uniform float radius;
uniform vec3 color;
uniform float brightness;

void main()
{
float dist = length(lightPos - gl_FragCoord.xy);
float alpha = dist/radius;
vec4 color = vec4(color.r - alpha, color.g - alpha, color.b - alpha, brightness);
gl_FragColor = color;
}