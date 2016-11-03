/*
 MIT License
 Copyright (c) 2016 Ruben Moreno Montoliu <ruben3d@gmail.com>
 */
uniform sampler2D sCanvas;
uniform sampler2D sTable;

// Workaround from:
// https://github.com/jeromeetienne/threex.coloradjust/blob/master/threex.coloradjust.js
vec4 sampleAs3DTexture(sampler2D texture, vec3 uv, float width) {
	float sliceSize = 1.0 / width;							// space of 1 slice
	float slicePixelSize = sliceSize / width;				// space of 1 pixel
	float sliceInnerSize = slicePixelSize * (width - 1.0);	// space of width pixels
	float zSlice0 = min(floor(uv.z * width), width - 1.0);
	float zSlice1 = min(zSlice0 + 1.0, width - 1.0);
	float xOffset = slicePixelSize * 0.5 + uv.x * sliceInnerSize;
	float s0 = xOffset + (zSlice0 * sliceSize);
	float s1 = xOffset + (zSlice1 * sliceSize);
	vec4 slice0Color = texture2D(texture, vec2(s0, uv.y));
	vec4 slice1Color = texture2D(texture, vec2(s1, uv.y));
	float zOffset = mod(uv.z * width, 1.0);
	vec4 result = mix(slice0Color, slice1Color, zOffset);
	return result;
}

void main()
{
	// If SFML supports 3D textures in the future...
	// vec3 srcColor = texture2D(sCanvas, gl_TexCoord[0].st).rgb;
	// vec4 dstColor = texture3D(sTable, srcColor).rgb;

	vec3 srcColor = texture2D(sCanvas, gl_TexCoord[0].st).rgb;
	vec3 dstColor = sampleAs3DTexture(sTable, srcColor, 16).rgb;

	//float gamma = 2.2;
	//dstColor = pow(dstColor, vec3(1.0/gamma));

	gl_FragColor = vec4(dstColor, 1.0);
}
