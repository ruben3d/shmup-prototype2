/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
//
// tile-base-emission.fs - Created on 2016.06.11
//

uniform sampler2D sDiffuse;
uniform sampler2D sSpecular;
uniform sampler2D sNormal;
uniform sampler2D sEmission;
uniform vec3 uSunDir; // L
uniform vec4 uSunLight;
uniform vec4 uAmbientLight;

void main()
{
	vec3 N = normalize(2.0 * texture2D(sNormal, gl_TexCoord[0].st).rgb + vec3(-1));

	vec4 Kd = texture2D(sDiffuse, gl_TexCoord[0].st);

	vec3 ambient = Kd.rgb * uAmbientLight.rgb;

	float f = max(dot(uSunDir, N), 0.0);
	vec3 diffuse = Kd.rgb * uSunLight.rgb * f;

	vec3 R = reflect(-uSunDir, N);
	float specDot = max(0.0, dot(vec3(0,0,1), R));
	float specFactor = pow(specDot, 32.0) * texture2D(sSpecular, gl_TexCoord[0].st).r;
	vec3 specular = uSunLight.rgb * specFactor;

	vec3 emission = texture2D(sEmission, gl_TexCoord[0].st).xyz;

	vec3 total = ambient;
	total += diffuse;
	total += specular;
	total += emission;
	gl_FragColor = vec4(total * gl_Color.rgb, gl_Color.a * Kd.a );
}
