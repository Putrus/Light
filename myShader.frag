
uniform vec2 lightPos;
uniform float radius;

void main()
{

float dist = length(lightPos - gl_FragCoord.xy);

float alpha = 1.0f-dist/radius;
vec4 color = vec4(1.0f,1.0f,1.0f,alpha);

gl_FragColor = color;
}