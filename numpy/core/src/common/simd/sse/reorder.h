#ifndef NPY_SIMD
    #error "Not a standalone header"
#endif

#ifndef _NPY_SIMD_SSE_REORDER_H
#define _NPY_SIMD_SSE_REORDER_H

// combine lower part of two vectors
#define npyv_combinel_u8  _mm_unpacklo_epi64
#define npyv_combinel_s8  _mm_unpacklo_epi64
#define npyv_combinel_u16 _mm_unpacklo_epi64
#define npyv_combinel_s16 _mm_unpacklo_epi64
#define npyv_combinel_u32 _mm_unpacklo_epi64
#define npyv_combinel_s32 _mm_unpacklo_epi64
#define npyv_combinel_u64 _mm_unpacklo_epi64
#define npyv_combinel_s64 _mm_unpacklo_epi64
#define npyv_combinel_f32(A, B) _mm_castsi128_ps(_mm_unpacklo_epi64(_mm_castps_si128(A), _mm_castps_si128(B)))
#define npyv_combinel_f64 _mm_unpacklo_pd

// combine higher part of two vectors
#define npyv_combineh_u8  _mm_unpackhi_epi64
#define npyv_combineh_s8  _mm_unpackhi_epi64
#define npyv_combineh_u16 _mm_unpackhi_epi64
#define npyv_combineh_s16 _mm_unpackhi_epi64
#define npyv_combineh_u32 _mm_unpackhi_epi64
#define npyv_combineh_s32 _mm_unpackhi_epi64
#define npyv_combineh_u64 _mm_unpackhi_epi64
#define npyv_combineh_s64 _mm_unpackhi_epi64
#define npyv_combineh_f32(A, B) _mm_castsi128_ps(_mm_unpackhi_epi64(_mm_castps_si128(A), _mm_castps_si128(B)))
#define npyv_combineh_f64 _mm_unpackhi_pd

// combine two vectors from lower and higher parts of two other vectors
NPY_FINLINE npyv_m128ix2 npyv__combine(__m128i a, __m128i b)
{
    npyv_m128ix2 r;
    r.val[0] = npyv_combinel_u8(a, b);
    r.val[1] = npyv_combineh_u8(a, b);
    return r;
}
NPY_FINLINE npyv_f32x2 npyv_combine_f32(__m128 a, __m128 b)
{
    npyv_f32x2 r;
    r.val[0] = npyv_combinel_f32(a, b);
    r.val[1] = npyv_combineh_f32(a, b);
    return r;
}
NPY_FINLINE npyv_f64x2 npyv_combine_f64(__m128d a, __m128d b)
{
    npyv_f64x2 r;
    r.val[0] = npyv_combinel_f64(a, b);
    r.val[1] = npyv_combineh_f64(a, b);
    return r;
}

#define npyv_combine_u8  npyv__combine
#define npyv_combine_s8  npyv__combine
#define npyv_combine_u16 npyv__combine
#define npyv_combine_s16 npyv__combine
#define npyv_combine_u32 npyv__combine
#define npyv_combine_s32 npyv__combine
#define npyv_combine_u64 npyv__combine
#define npyv_combine_s64 npyv__combine

// shuffle vector lanes
#define  npyv_shuffle_f32 _mm_shuffle_ps
#define  npyv_shuffle_f64 _mm_shuffle_pd

// interleave two vectors
#define NPYV_IMPL_SSE_ZIP(T_VEC, SFX, INTR_SFX)            \
    NPY_FINLINE T_VEC##x2 npyv_zip_##SFX(T_VEC a, T_VEC b) \
    {                                                      \
        T_VEC##x2 r;                                       \
        r.val[0] = _mm_unpacklo_##INTR_SFX(a, b);          \
        r.val[1] = _mm_unpackhi_##INTR_SFX(a, b);          \
        return r;                                          \
    }

NPYV_IMPL_SSE_ZIP(npyv_u8,  u8,  epi8)
NPYV_IMPL_SSE_ZIP(npyv_s8,  s8,  epi8)
NPYV_IMPL_SSE_ZIP(npyv_u16, u16, epi16)
NPYV_IMPL_SSE_ZIP(npyv_s16, s16, epi16)
NPYV_IMPL_SSE_ZIP(npyv_u32, u32, epi32)
NPYV_IMPL_SSE_ZIP(npyv_s32, s32, epi32)
NPYV_IMPL_SSE_ZIP(npyv_u64, u64, epi64)
NPYV_IMPL_SSE_ZIP(npyv_s64, s64, epi64)
NPYV_IMPL_SSE_ZIP(npyv_f32, f32, ps)
NPYV_IMPL_SSE_ZIP(npyv_f64, f64, pd)

#endif // _NPY_SIMD_SSE_REORDER_H
