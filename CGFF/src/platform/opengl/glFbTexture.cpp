#include "glFbTexture.h"
#include "glContext.h"

namespace CGFF {

    GLFbTexture::GLFbTexture(int width, int height, const TextureParameters& parameters, const QString& name)
        : m_name(name)
        , m_width(width)
        , m_height(height)
        , m_glTextureId(0)
        , m_textureParams(parameters)
    {
        init();
    }

    GLFbTexture::~GLFbTexture()
    {
    }

    void GLFbTexture::bind(uint slot)
    {
        GL->glActiveTexture(GL_TEXTURE0 + slot);
        GL->glBindTexture(GL_TEXTURE_2D, m_glTextureId);
    }

    void GLFbTexture::unBind(uint slot)
    {
        GL->glActiveTexture(GL_TEXTURE0 + slot);
        GL->glBindTexture(GL_TEXTURE_2D, 0);
    }

    GLenum GLFbTexture::toOpenGlPixelFormat(QOpenGLTexture::PixelFormat format)
    {
        switch (format)
        {
        case QOpenGLTexture::PixelFormat::NoSourceFormat:
            return GL_NONE;// GL_NONE
        case QOpenGLTexture::PixelFormat::Red:
            return GL_RED;// GL_RED
        case QOpenGLTexture::PixelFormat::RG:
            return GL_RG;    // GL_RG
        case QOpenGLTexture::PixelFormat::RGB:
            return GL_RGB;    // GL_RGB
        case QOpenGLTexture::PixelFormat::BGR:
            return GL_BGR;    // GL_BGR
        case QOpenGLTexture::PixelFormat::RGBA:
            return GL_RGBA;    // GL_RGBA
        case QOpenGLTexture::PixelFormat::BGRA:
            return GL_BGRA;   // GL_BGRA
        case QOpenGLTexture::PixelFormat::Red_Integer:
            return GL_RED_INTEGER;    // GL_RED_INTEGER
        case QOpenGLTexture::PixelFormat::RG_Integer:
            return GL_RG_INTEGER;   // GL_RG_INTEGER
        case QOpenGLTexture::PixelFormat::RGB_Integer:
            return GL_RGB_INTEGER;    // GL_RGB_INTEGER
        case QOpenGLTexture::PixelFormat::BGR_Integer:
            return GL_BGR_INTEGER;    // GL_BGR_INTEGER
        case QOpenGLTexture::PixelFormat::RGBA_Integer:
            return GL_RGBA_INTEGER;    // GL_RGBA_INTEGER
        case QOpenGLTexture::PixelFormat::BGRA_Integer:
            return GL_BGRA_INTEGER;    // GL_BGRA_INTEGER
        case QOpenGLTexture::PixelFormat::Stencil:
            return GL_STENCIL_INDEX;   // GL_STENCIL_INDEX
        case QOpenGLTexture::PixelFormat::Depth:
            return GL_DEPTH_COMPONENT;    // GL_DEPTH_COMPONENT
        case QOpenGLTexture::PixelFormat::DepthStencil:
            return GL_DEPTH_STENCIL;   // GL_DEPTH_STENCIL
        case QOpenGLTexture::PixelFormat::Alpha:
            return GL_ALPHA;    // GL_ALPHA
        case QOpenGLTexture::PixelFormat::Luminance:
            return GL_LUMINANCE; // GL_LUMINANCE
        case QOpenGLTexture::PixelFormat::LuminanceAlpha:
            return GL_LUMINANCE_ALPHA;     // GL_LUMINANCE_ALPHA
        }
        return GL_NONE;
    }
    GLuint GLFbTexture::toOpenGlTextureFormat(QOpenGLTexture::TextureFormat format)
    {
        switch (format)
        {
        case QOpenGLTexture::TextureFormat::NoFormat:
            return GL_NONE;// GL_NONE

        // Unsigned normalized formats
        case QOpenGLTexture::TextureFormat::R8_UNorm:
            return GL_R8;    // GL_R8
        case QOpenGLTexture::TextureFormat::RG8_UNorm:
            return GL_RG8;     // GL_RG8
        case QOpenGLTexture::TextureFormat::RGB8_UNorm:
            return GL_RGB8;    // GL_RGB8
        case QOpenGLTexture::TextureFormat::RGBA8_UNorm:
            return GL_RGBA8;     // GL_RGBA8

        case QOpenGLTexture::TextureFormat::R16_UNorm:
            return GL_R16;    // GL_R16
        case QOpenGLTexture::TextureFormat::RG16_UNorm:
            return GL_RG16;    // GL_RG16
        case QOpenGLTexture::TextureFormat::RGB16_UNorm:
            return GL_RGB16;     // GL_RGB16
        case QOpenGLTexture::TextureFormat::RGBA16_UNorm:
            return GL_RGBA16;     // GL_RGBA16

        // Signed normalized formats
        case QOpenGLTexture::TextureFormat::R8_SNorm:
            return GL_R8_SNORM;    // GL_R8_SNORM
        case QOpenGLTexture::TextureFormat::RG8_SNorm:
            return GL_RG8_SNORM;     // GL_RG8_SNORM
        case QOpenGLTexture::TextureFormat::RGB8_SNorm:
            return GL_RGB8_SNORM;    // GL_RGB8_SNORM
        case QOpenGLTexture::TextureFormat::RGBA8_SNorm:
            return GL_RGBA8_SNORM;    // GL_RGBA8_SNORM

        case QOpenGLTexture::TextureFormat::R16_SNorm:
            return GL_R16_SNORM;     // GL_R16_SNORM
        case QOpenGLTexture::TextureFormat::RG16_SNorm:
            return GL_RG16_SNORM;     // GL_RG16_SNORM
        case QOpenGLTexture::TextureFormat::RGB16_SNorm:
            return GL_RGB16_SNORM;    // GL_RGB16_SNORM
        case QOpenGLTexture::TextureFormat::RGBA16_SNorm:
            return GL_RGBA16_SNORM;    // GL_RGBA16_SNORM

        // Unsigned integer formats
        case QOpenGLTexture::TextureFormat::R8U:
            return GL_R8UI;   // GL_R8UI
        case QOpenGLTexture::TextureFormat::RG8U:
            return GL_RG8UI;  // GL_RG8UI
        case QOpenGLTexture::TextureFormat::RGB8U:
            return GL_RGB8UI;  // GL_RGB8UI
        case QOpenGLTexture::TextureFormat::RGBA8U:
            return GL_RGBA8UI;  // GL_RGBA8UI

        case QOpenGLTexture::TextureFormat::R16U:
            return GL_R16UI;     // GL_R16UI
        case QOpenGLTexture::TextureFormat::RG16U:
            return GL_RG16UI;    // GL_RG16UI
        case QOpenGLTexture::TextureFormat::RGB16U:
            return GL_RGB16UI;    // GL_RGB16UI
        case QOpenGLTexture::TextureFormat::RGBA16U:
            return GL_RGBA16UI;    // GL_RGBA16UI

        case QOpenGLTexture::TextureFormat::R32U:
            return GL_R32UI;     // GL_R32UI
        case QOpenGLTexture::TextureFormat::RG32U:
            return GL_RG32UI;     // GL_RG32UI
        case QOpenGLTexture::TextureFormat::RGB32U:
            return GL_RGB32UI;     // GL_RGB32UI
        case QOpenGLTexture::TextureFormat::RGBA32U:
            return GL_RGBA32UI;    // GL_RGBA32UI

        // Signed integer formats
        case QOpenGLTexture::TextureFormat::R8I:
            return GL_R8I;   // GL_R8I
        case QOpenGLTexture::TextureFormat::RG8I:
            return GL_RG8I;    // GL_RG8I
        case QOpenGLTexture::TextureFormat::RGB8I:
            return GL_RGB8I;   // GL_RGB8I
        case QOpenGLTexture::TextureFormat::RGBA8I:
            return GL_RGBA8I;    // GL_RGBA8I

        case QOpenGLTexture::TextureFormat::R16I:
            return GL_R16I;    // GL_R16I
        case QOpenGLTexture::TextureFormat::RG16I:
            return GL_RG16I;    // GL_RG16I
        case QOpenGLTexture::TextureFormat::RGB16I:
            return GL_RGB16I;    // GL_RGB16I
        case QOpenGLTexture::TextureFormat::RGBA16I:
            return GL_RGBA16I;    // GL_RGBA16I

        case QOpenGLTexture::TextureFormat::R32I:
            return GL_R32I;  // GL_R32I
        case QOpenGLTexture::TextureFormat::RG32I:
            return GL_RG32I;    // GL_RG32I
        case QOpenGLTexture::TextureFormat::RGB32I:
            return GL_RGB32I;     // GL_RGB32I
        case QOpenGLTexture::TextureFormat::RGBA32I:
            return GL_RGBA32I;    // GL_RGBA32I

        // Floating point formats
        case QOpenGLTexture::TextureFormat::R16F:
            return GL_R16F;    // GL_R16F
        case QOpenGLTexture::TextureFormat::RG16F:
            return GL_RG16F;   // GL_RG16F
        case QOpenGLTexture::TextureFormat::RGB16F:
            return GL_RGB16F;  // GL_RGB16F
        case QOpenGLTexture::TextureFormat::RGBA16F:
            return GL_RGBA16F;  // GL_RGBA16F

        case QOpenGLTexture::TextureFormat::R32F:
            return GL_R32F;   // GL_R32F
        case QOpenGLTexture::TextureFormat::RG32F:
            return GL_RG32F;    // GL_RG32F
        case QOpenGLTexture::TextureFormat::RGB32F:
            return GL_RGB32F;    // GL_RGB32F
        case QOpenGLTexture::TextureFormat::RGBA32F:
            return GL_RGBA32F;   // GL_RGBA32F

       // Packed formats
        case QOpenGLTexture::TextureFormat::RGB9E5:
            return GL_RGB9_E5;    // GL_RGB9_E5
        case QOpenGLTexture::TextureFormat::RG11B10F:
            return GL_R11F_G11F_B10F;    // GL_R11F_G11F_B10F
        case QOpenGLTexture::TextureFormat::RG3B2:
            return GL_R3_G3_B2;   // GL_R3_G3_B2
        case QOpenGLTexture::TextureFormat::R5G6B5:
            return GL_RGB565;    // GL_RGB565
        case QOpenGLTexture::TextureFormat::RGB5A1:
            return GL_RGB5_A1;    // GL_RGB5_A1
        case QOpenGLTexture::TextureFormat::RGBA4:
            return GL_RGBA4;   // GL_RGBA4
        case QOpenGLTexture::TextureFormat::RGB10A2:
            return GL_RGB10_A2UI;   // GL_RGB10_A2UI

         // Depth formats
        case QOpenGLTexture::TextureFormat::D16:
            return GL_DEPTH_COMPONENT16;    // GL_DEPTH_COMPONENT16
        case QOpenGLTexture::TextureFormat::D24:
            return GL_DEPTH_COMPONENT24;   // GL_DEPTH_COMPONENT24
        case QOpenGLTexture::TextureFormat::D24S8:
            return GL_DEPTH24_STENCIL8;    // GL_DEPTH24_STENCIL8
        case QOpenGLTexture::TextureFormat::D32:
            return GL_DEPTH_COMPONENT32;   // GL_DEPTH_COMPONENT32
        case QOpenGLTexture::TextureFormat::D32F:
            return GL_DEPTH_COMPONENT32F;    // GL_DEPTH_COMPONENT32F
        case QOpenGLTexture::TextureFormat::D32FS8X24:
            return GL_DEPTH32F_STENCIL8;   // GL_DEPTH32F_STENCIL8
        case QOpenGLTexture::TextureFormat::S8:
            return GL_STENCIL_INDEX8;    // GL_STENCIL_INDEX8

                        // Compressed formats
        case QOpenGLTexture::TextureFormat::RGB_DXT1:
            return GL_COMPRESSED_RGB_S3TC_DXT1_EXT;  // GL_COMPRESSED_RGB_S3TC_DXT1_EXT
        case QOpenGLTexture::TextureFormat::RGBA_DXT1:
            return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;    // GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
        case QOpenGLTexture::TextureFormat::RGBA_DXT3:
            return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;  // GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
        case QOpenGLTexture::TextureFormat::RGBA_DXT5:
            return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;    // GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
        case QOpenGLTexture::TextureFormat::R_ATI1N_UNorm:
            return GL_COMPRESSED_RED_RGTC1;   // GL_COMPRESSED_RED_RGTC1
        case QOpenGLTexture::TextureFormat::R_ATI1N_SNorm:
            return GL_COMPRESSED_SIGNED_RED_RGTC1;  // GL_COMPRESSED_SIGNED_RED_RGTC1
        case QOpenGLTexture::TextureFormat::RG_ATI2N_UNorm:
            return GL_COMPRESSED_RG_RGTC2;   // GL_COMPRESSED_RG_RGTC2
        case QOpenGLTexture::TextureFormat::RG_ATI2N_SNorm:
            return GL_COMPRESSED_SIGNED_RG_RGTC2;   // GL_COMPRESSED_SIGNED_RG_RGTC2
        case QOpenGLTexture::TextureFormat::RGB_BP_UNSIGNED_FLOAT:
            return GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB;    // GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB
        case QOpenGLTexture::TextureFormat::RGB_BP_SIGNED_FLOAT:
            return GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB;    // GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB
        case QOpenGLTexture::TextureFormat::RGB_BP_UNorm:
            return GL_COMPRESSED_RGBA_BPTC_UNORM_ARB;    // GL_COMPRESSED_RGBA_BPTC_UNORM_ARB
        case QOpenGLTexture::TextureFormat::R11_EAC_UNorm:
            return GL_COMPRESSED_R11_EAC;    // GL_COMPRESSED_R11_EAC
        case QOpenGLTexture::TextureFormat::R11_EAC_SNorm:
            return GL_COMPRESSED_SIGNED_R11_EAC;   // GL_COMPRESSED_SIGNED_R11_EAC
        case QOpenGLTexture::TextureFormat::RG11_EAC_UNorm:
            return GL_COMPRESSED_RG11_EAC;   // GL_COMPRESSED_RG11_EAC
        case QOpenGLTexture::TextureFormat::RG11_EAC_SNorm:
            return GL_COMPRESSED_SIGNED_RG11_EAC;    // GL_COMPRESSED_SIGNED_RG11_EAC
        case QOpenGLTexture::TextureFormat::RGB8_ETC2:
            return GL_COMPRESSED_RGB8_ETC2;    // GL_COMPRESSED_RGB8_ETC2
        case QOpenGLTexture::TextureFormat::SRGB8_ETC2:
            return GL_COMPRESSED_SRGB8_ETC2;    // GL_COMPRESSED_SRGB8_ETC2
        case QOpenGLTexture::TextureFormat::RGB8_PunchThrough_Alpha1_ETC2:
            return GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2; // GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2
        case QOpenGLTexture::TextureFormat::SRGB8_PunchThrough_Alpha1_ETC2:
            return GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2; // GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2
        case QOpenGLTexture::TextureFormat::RGBA8_ETC2_EAC:
            return GL_COMPRESSED_RGBA8_ETC2_EAC;   // GL_COMPRESSED_RGBA8_ETC2_EAC
        case QOpenGLTexture::TextureFormat::SRGB8_Alpha8_ETC2_EAC:
            return GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC;    // GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC

        // sRGB formats
        case QOpenGLTexture::TextureFormat::SRGB8:
            return GL_SRGB8;    // GL_SRGB8
        case QOpenGLTexture::TextureFormat::SRGB8_Alpha8:
            return GL_SRGB8_ALPHA8;    // GL_SRGB8_ALPHA8
        case QOpenGLTexture::TextureFormat::SRGB_DXT1:
            return GL_COMPRESSED_SRGB_S3TC_DXT1_EXT;    // GL_COMPRESSED_SRGB_S3TC_DXT1_EXT
        case QOpenGLTexture::TextureFormat::SRGB_Alpha_DXT1:
            return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT;    // GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT
        case QOpenGLTexture::TextureFormat::SRGB_Alpha_DXT3:
            return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT;    // GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT
        case QOpenGLTexture::TextureFormat::SRGB_Alpha_DXT5:
            return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT;    // GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT
        case QOpenGLTexture::TextureFormat::SRGB_BP_UNorm:
            return GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB;    // GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB

        // ES 2 formats
        case QOpenGLTexture::TextureFormat::DepthFormat:
            return GL_DEPTH_COMPONENT;    // GL_DEPTH_COMPONENT
        case QOpenGLTexture::TextureFormat::AlphaFormat:
            return GL_ALPHA;    // GL_ALPHA
        case QOpenGLTexture::TextureFormat::RGBFormat:
            return GL_RGB;   // GL_RGB
        case QOpenGLTexture::TextureFormat::RGBAFormat:
            return GL_RGBA;    // GL_RGBA
        case QOpenGLTexture::TextureFormat::LuminanceFormat:
            return GL_LUMINANCE;   // GL_LUMINANCE
        case QOpenGLTexture::TextureFormat::LuminanceAlphaFormat:
            return GL_LUMINANCE_ALPHA;
        }

        return GL_NONE;
    }
    GLenum GLFbTexture::toOpenGlPixelType(QOpenGLTexture::PixelType type)
    {
        switch (type)
        {
        case QOpenGLTexture::PixelType::NoPixelType:
            return GL_NONE;// GL_NONE
        case QOpenGLTexture::PixelType::Int8:
            return GL_BYTE;    // GL_BYTE
        case QOpenGLTexture::PixelType::UInt8:
            return GL_UNSIGNED_BYTE;   // GL_UNSIGNED_BYTE
        case QOpenGLTexture::PixelType::Int16:
            return GL_SHORT;    // GL_SHORT
        case QOpenGLTexture::PixelType::UInt16:
            return GL_UNSIGNED_SHORT;    // GL_UNSIGNED_SHORT
        case QOpenGLTexture::PixelType::Int32:
            return GL_INT;   // GL_INT
        case QOpenGLTexture::PixelType::UInt32:
            return GL_UNSIGNED_INT;    // GL_UNSIGNED_INT
        case QOpenGLTexture::PixelType::Float16:
            return GL_HALF_FLOAT;    // GL_HALF_FLOAT
        case QOpenGLTexture::PixelType::Float32:
            return GL_FLOAT;   // GL_FLOAT
        case QOpenGLTexture::PixelType::UInt32_RGB9_E5:
            return GL_UNSIGNED_INT_5_9_9_9_REV;    // GL_UNSIGNED_INT_5_9_9_9_REV
        case QOpenGLTexture::PixelType::UInt32_RG11B10F:
            return GL_UNSIGNED_INT_10F_11F_11F_REV;   // GL_UNSIGNED_INT_10F_11F_11F_REV
        case QOpenGLTexture::PixelType::UInt8_RG3B2:
            return GL_UNSIGNED_BYTE_3_3_2; // GL_UNSIGNED_BYTE_3_3_2
        case QOpenGLTexture::PixelType::UInt8_RG3B2_Rev:
            return GL_UNSIGNED_BYTE_2_3_3_REV; // GL_UNSIGNED_BYTE_2_3_3_REV
        case QOpenGLTexture::PixelType::UInt16_RGB5A1:
            return GL_UNSIGNED_SHORT_5_5_5_1;   // GL_UNSIGNED_SHORT_5_5_5_1
        case QOpenGLTexture::PixelType::UInt16_RGB5A1_Rev:
            return GL_UNSIGNED_SHORT_1_5_5_5_REV;  // GL_UNSIGNED_SHORT_1_5_5_5_REV
        case QOpenGLTexture::PixelType::UInt16_R5G6B5:
            return GL_UNSIGNED_SHORT_5_6_5;    // GL_UNSIGNED_SHORT_5_6_5
        case QOpenGLTexture::PixelType::UInt16_R5G6B5_Rev:
            return GL_UNSIGNED_SHORT_5_6_5_REV;    // GL_UNSIGNED_SHORT_5_6_5_REV
        case QOpenGLTexture::PixelType::UInt16_RGBA4:
            return GL_UNSIGNED_SHORT_4_4_4_4;   // GL_UNSIGNED_SHORT_4_4_4_4
        case QOpenGLTexture::PixelType::UInt16_RGBA4_Rev:
            return GL_UNSIGNED_SHORT_4_4_4_4_REV;   // GL_UNSIGNED_SHORT_4_4_4_4_REV
        case QOpenGLTexture::PixelType::UInt32_RGBA8:
            return GL_UNSIGNED_INT_8_8_8_8;  // GL_UNSIGNED_INT_8_8_8_8
        case QOpenGLTexture::PixelType::UInt32_RGBA8_Rev:
            return GL_UNSIGNED_INT_8_8_8_8_REV;   // GL_UNSIGNED_INT_8_8_8_8_REV
        case QOpenGLTexture::PixelType::UInt32_RGB10A2:
            return GL_UNSIGNED_INT_10_10_10_2;  // GL_UNSIGNED_INT_10_10_10_2
        case QOpenGLTexture::PixelType::UInt32_RGB10A2_Rev:
            return GL_UNSIGNED_INT_2_10_10_10_REV;    // GL_UNSIGNED_INT_2_10_10_10_REV
        case QOpenGLTexture::PixelType::UInt32_D24S8:
            return GL_UNSIGNED_INT_24_8;  // GL_UNSIGNED_INT_24_8
        case QOpenGLTexture::PixelType::Float32_D32_UInt32_S8_X24:
            return GL_FLOAT_32_UNSIGNED_INT_24_8_REV; // GL_FLOAT_32_UNSIGNED_INT_24_8_REV
        }

        return GL_NONE;

    }
    GLenum GLFbTexture::toOpenGlFilter(QOpenGLTexture::Filter filter)
    {
        switch (filter)
        {
        case QOpenGLTexture::Filter::Nearest:
            return GL_NEAREST;// GL_NEAREST
        case QOpenGLTexture::Filter::Linear:
            return GL_LINEAR;   // GL_LINEAR
        case QOpenGLTexture::Filter::NearestMipMapNearest:
            return GL_NEAREST_MIPMAP_NEAREST;  // GL_NEAREST_MIPMAP_NEAREST
        case QOpenGLTexture::Filter::NearestMipMapLinear:
            return GL_NEAREST_MIPMAP_LINEAR;  // GL_NEAREST_MIPMAP_LINEAR
        case QOpenGLTexture::Filter::LinearMipMapNearest:
            return GL_LINEAR_MIPMAP_NEAREST;   // GL_LINEAR_MIPMAP_NEAREST
        case QOpenGLTexture::Filter::LinearMipMapLinear:
            return GL_LINEAR_MIPMAP_LINEAR;  // GL_LINEAR_MIPMAP_LINEAR
        }

        return GL_NEAREST;
    }
    GLenum GLFbTexture::toOpenGlWrap(QOpenGLTexture::WrapMode wrap)
    {
        switch (wrap)
        {
        case QOpenGLTexture::WrapMode::Repeat:
            return GL_REPEAT;// GL_REPEAT
        case QOpenGLTexture::WrapMode::MirroredRepeat:
            return GL_MIRRORED_REPEAT; // GL_MIRRORED_REPEAT
        case QOpenGLTexture::WrapMode::ClampToEdge:
            return GL_CLAMP_TO_EDGE;// GL_CLAMP_TO_EDGE
        case QOpenGLTexture::WrapMode::ClampToBorder:
            return GL_CLAMP_TO_BORDER; // GL_CLAMP_TO_BORDER
        }

        return GL_REPEAT;
    }

    void GLFbTexture::init()
    {
        GL->glGenTextures(1, &m_glTextureId);
        GL->glBindTexture(GL_TEXTURE_2D, m_glTextureId);
        GL->glTexImage2D(GL_TEXTURE_2D, 0, toOpenGlTextureFormat(m_textureParams.gl_textureFormat), m_width, m_height, 0, 
            toOpenGlPixelFormat(m_textureParams.gl_pixelFormat), toOpenGlPixelType(m_textureParams.gl_pixelType), NULL);
        GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, toOpenGlFilter(m_textureParams.gl_filter));
        GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, toOpenGlFilter(m_textureParams.gl_filter));
    }
}