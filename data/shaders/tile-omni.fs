/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// tile-omni.fs - Created on 2016.06.11
//

uniform sampler2D sDiffuse;
uniform sampler2D sSpecular;
uniform sampler2D sNormal;
uniform sampler2D sHeight;

uniform vec3 uLightPos;
uniform vec4 uLightColor;
uniform float uLightRadius;

uniform float uTileHeight;

varying vec2 vWorldPos;

void main()
{
	vec3 N = normalize(2.0 * texture2D(sNormal, gl_TexCoord[0].st).rgb + vec3(-1));
	vec3 PtoL = uLightPos - vec3(vWorldPos, uTileHeight + texture2D(sHeight, gl_TexCoord[0].st).r * 32.0);
	vec3 L = normalize(PtoL);

	vec4 Kd = texture2D(sDiffuse, gl_TexCoord[0].st);
	float f = max(dot(L, N), 0.0);
	vec3 diffuse = Kd.rgb * uLightColor.rgb * f;

	vec3 R = reflect(-L, N);
	float specDot = max(0.0, dot(vec3(0,0,1), R));
	float specFactor = pow(specDot, 32.0) * texture2D(sSpecular, gl_TexCoord[0].st).r;
	vec3 specular = uLightColor.rgb * specFactor;

	float intensity = max( (uLightRadius - length(PtoL)) / uLightRadius, 0.0 );

	vec3 total = diffuse;
	total += specular;
	total *= intensity;
	gl_FragColor = vec4(total * gl_Color.rgb, gl_Color.a * Kd.a );
}
