/*
 * Copyright (C) 2018  Fuzhou Rockchip Electronics Co., Ltd. All rights reserved.
 * Authors:
 *     lihuang <putin.li@rock-chips.com>
 *     libin <bin.li@rock-chips.com>
 *
 * This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * BY DOWNLOADING, INSTALLING, COPYING, SAVING OR OTHERWISE USING THIS SOFTWARE,
 * YOU ACKNOWLEDGE THAT YOU AGREE THE SOFTWARE RECEIVED FORM ROCKCHIP IS PROVIDED
 * TO YOU ON AN "AS IS" BASIS and ROCKCHP DISCLAIMS ANY AND ALL WARRANTIES AND
 * REPRESENTATIONS WITH RESPECT TO SUCH FILE, WHETHER EXPRESS, IMPLIED, STATUTORY
 * OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY IMPLIED WARRANTIES OF TITLE,
 * NON-INFRINGEMENT, MERCHANTABILITY, SATISFACTROY QUALITY, ACCURACY OR FITNESS FOR
 * A PARTICULAR PURPOSE.
 */

#ifndef _rockchip_normal_rga_h_
#define _rockchip_normal_rga_h_

#ifdef ANDROID_7_DRM
#define RGA_BUF_GEM_TYPE_MASK      0xC0
#define RGA_BUF_GEM_TYPE_DMA       0x80
#endif

#include <stdint.h>
#include <vector>
#include <sys/types.h>

//#include <system/window.h>

#include <utils/Thread.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

//////////////////////////////////////////////////////////////////////////////////
#include <hardware/hardware.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

#include <utils/Atomic.h>
#include <utils/Errors.h>
#include <utils/Log.h>
#include <ui/PixelFormat.h>

#include <sys/mman.h>
#include <linux/stddef.h>

#include <hardware/rga.h>
#include "stdio.h"

#include "drmrga.h"
#include "NormalRgaContext.h"


int         NormalRgaInitTables();

int         NormalRgaPaletteTable(buffer_handle_t dst, 
                                           unsigned int v, drm_rga_t *rects);

int         NormalRgaStereo(buffer_handle_t src,
                                                buffer_handle_t dst,int div);
int         NormalRgaScale();
int         NormalRgaRoate();
int         NormalRgaRoateScale();
int         NormalRgaGetRects(buffer_handle_t src, buffer_handle_t dst,
                                int *sType, int *dType, drm_rga_t* tmpRects);
/*
@fun NormalRgaSetRects:For use to set the rects esayly

@param rect:The rect user want to set,like setting the src rect:
    drm_rga_t rects;
    NormalRgaSetRects(rects.src,0,0,1920,1080,1920,NV12);
    mean to set the src rect to the value.
*/
int         checkRectForRga(rga_rect_t rect);
int         isRectValid(rga_rect_t rect);
int         NormalRgaGetRect(buffer_handle_t hnd, rga_rect_t *rect);
int         NormalRgaGetMmuType(buffer_handle_t hnd, int *mmuType);

int         NormalRgaSetRect(rga_rect_t *rect, int x, int y,
                                               int w, int h, int s, int f);
void        NormalRgaSetLogOnceFlag(int log);
void        NormalRgaSetAlwaysLogFlag(bool log);
void        NormalRgaLogOutRgaReq(struct rga_req rgaReg);
void        is_debug_log(void);
int         is_out_log(void);
int         hwc_get_int_property(const char* pcProperty, const char* default_value);

int         NormalRgaSetFdsOffsets(struct rga_req *req,
                                uint16_t src_fd,     uint16_t dst_fd,
                                uint32_t src_offset, uint32_t dst_offset);

int         NormalRgaSetSrcActiveInfo(struct rga_req *req,
                                unsigned int width, unsigned int height,
                                unsigned int x_off, unsigned int y_off);


#if defined(__arm64__) || defined(__aarch64__)
int         NormalRgaSetSrcVirtualInfo(struct rga_req *req,
        	unsigned long yrgb_addr,unsigned long uv_addr,unsigned long v_addr,
            unsigned int vir_w ,unsigned int vir_h, unsigned char format,
                                            unsigned char a_swap_en);
#else
int         NormalRgaSetSrcVirtualInfo(struct rga_req *req,
        	unsigned int yrgb_addr, unsigned int uv_addr,unsigned int v_addr,          
        	unsigned int vir_w, unsigned int vir_h, unsigned char format, 
        	                                        unsigned char a_swap_en);
#endif


int         NormalRgaSetDstActiveInfo(struct rga_req *req,
                                    unsigned int width, unsigned int height,
                                    unsigned int x_off, unsigned int y_off);


#if defined(__arm64__) || defined(__aarch64__)
int         NormalRgaSetDstVirtualInfo(struct rga_req *msg,
        	unsigned long yrgb_addr,unsigned long uv_addr,unsigned long v_addr,
        	unsigned int  vir_w,    unsigned int vir_h,
        	RECT          *clip,    unsigned char format, unsigned char a_swap_en);
#else
int         NormalRgaSetDstVirtualInfo(struct rga_req *msg,
        	unsigned int yrgb_addr,unsigned int uv_addr,  unsigned int v_addr,
        	unsigned int vir_w,    unsigned int vir_h,
        	RECT           *clip,  unsigned char  format, unsigned char a_swap_en);
#endif


int         NormalRgaSetPatInfo(struct rga_req *msg,
            unsigned int width,unsigned int height,unsigned int x_off,
                               unsigned int y_off, unsigned int pat_format);

int         NormalRgaSetPatActiveInfo(struct rga_req *req,
                                    unsigned int width, unsigned int height,
                                    unsigned int x_off, unsigned int y_off);

#if defined(__arm64__) || defined(__aarch64__)
int         NormalRgaSetPatVirtualInfo(struct rga_req *msg,
        	unsigned long yrgb_addr,unsigned long uv_addr,unsigned long v_addr,
        	unsigned int  vir_w,    unsigned int vir_h,
        	RECT          *clip,    unsigned char format, unsigned char a_swap_en);
#else
int         NormalRgaSetPatVirtualInfo(struct rga_req *msg,
        	unsigned int yrgb_addr,unsigned int uv_addr,  unsigned int v_addr,
        	unsigned int vir_w,    unsigned int vir_h,
        	RECT           *clip,  unsigned char  format, unsigned char a_swap_en);
#endif

#if defined(__arm64__) || defined(__aarch64__)
int         NormalRgaSetRopMaskInfo(struct rga_req *msg,
	        unsigned long rop_mask_addr,unsigned int rop_mask_endian_mode);
#else
int         NormalRgaSetRopMaskInfo(struct rga_req *msg,
	        unsigned int rop_mask_addr,unsigned int rop_mask_endian_mode);
#endif


/* 0:alpha' = alpha + (alpha>>7) | alpha' = alpha */
/* 0 global alpha / 1 per pixel alpha / 2 mix mode */

/* porter duff alpha mode en */ 

/* use dst alpha  */

int         NormalRgaSetAlphaEnInfo(struct rga_req *msg,
    		unsigned int alpha_cal_mode, unsigned int alpha_mode,        
    		unsigned int global_a_value, unsigned int PD_en,             
    		unsigned int PD_mode,        unsigned int dst_alpha_en );     



int         NormalRgaSetRopEnInfo(struct rga_req *msg,
            		unsigned int ROP_mode, unsigned int ROP_code,
            		unsigned int color_mode,unsigned int solid_color);


int         NormalRgaSetFadingEnInfo(struct rga_req *msg,
	                unsigned char r,unsigned char g,unsigned char b);


int         NormalRgaSetSrcTransModeInfo(struct rga_req *msg,
        	unsigned char trans_mode,unsigned char a_en,unsigned char b_en,
        	unsigned char g_en,unsigned char r_en,unsigned int color_key_min,
        	unsigned int color_key_max,unsigned char zero_mode_en);

bool        NormalRgaIsBppFormat(int format);

bool        NormalRgaIsYuvFormat(int format);

bool        NormalRgaIsRgbFormat(int format);


// 0/near  1/bilnear  2/bicubic  
// 0/copy 1/rotate_scale 2/x_mirror 3/y_mirror 
// rotate angle     
// dither en flag   
// AA flag          
int         NormalRgaSetBitbltMode(struct rga_req *msg,
                	unsigned char scale_mode,  unsigned char rotate_mode, 
                	unsigned int  angle,       unsigned int  dither_en,   
                	unsigned int  AA_en,       unsigned int  yuv2rgb_mode);


/* 1bpp/2bpp/4bpp/8bpp */
/* src endian mode sel */
/* BPP1 = 0 */
/* BPP1 = 1 */
int         NormalRgaSetColorPaletteMode(struct rga_req *msg,
            		unsigned char  palette_mode,unsigned char  endian_mode, 
            		unsigned int  bpp1_0_color, unsigned int  bpp1_1_color);

/* gradient color part         */
 /* saturation mode             */
 /* patten fill or solid fill   */
/* solid color                 */
 /* pattern width               */
 /* pattern height              */  
 /* pattern x offset            */
 /* pattern y offset            */
 /* alpha en                    */
int         NormalRgaSetColorFillMode(
                struct rga_req *msg,                COLOR_FILL  *gr_color,
                unsigned char  gr_satur_mode,       unsigned char  cf_mode,              
                unsigned int color,                 unsigned short pat_width,
                unsigned short pat_height,          unsigned char pat_x_off,
                unsigned char pat_y_off,            unsigned char aa_en);


/* start point              */
/* end   point              */
/* line point drawing color */
/* line width               */
/* AA en                    */
/* last point en            */
int         NormalRgaSetLineDrawingMode(struct rga_req *msg,
        		POINT sp,                     POINT ep,                     
        		unsigned int color,           unsigned int line_width,      
        		unsigned char AA_en,          unsigned char last_point_en);



/* blur/sharpness   */
/* filter intensity */
/* dither_en flag   */

int         NormalRgaSetBlurSharpFilterMode(
            		struct rga_req *msg,         unsigned char filter_mode,   
            		unsigned char filter_type,   unsigned char dither_en);


int         NormalRgaSetPreScalingMode(
                            struct rga_req *msg, unsigned char dither_en);


/* LUT table addr      */
/* 1bpp/2bpp/4bpp/8bpp */
#if defined(__arm64__) || defined(__aarch64__)
int         NormalRgaUpdatePaletteTableMode(
            struct rga_req *msg,unsigned long LUT_addr,unsigned int palette_mode);
#else
int         NormalRgaUpdatePaletteTableMode(
            struct rga_req *msg,unsigned int LUT_addr, unsigned int palette_mode);
#endif


/* patten addr    */
/* patten width   */
/* patten height  */
/* patten format  */

int         NormalRgaUpdatePattenBuffMode(struct rga_req *msg,
                                unsigned int pat_addr, unsigned int w,        
                                unsigned int h,        unsigned int format);


#if defined(__arm64__) || defined(__aarch64__)
int         NormalRgaMmuInfo(struct rga_req *msg,
                    unsigned char  mmu_en,   unsigned char  src_flush,
                    unsigned char  dst_flush,unsigned char  cmd_flush,
                    unsigned long base_addr, unsigned char  page_size);
#else
int         NormalRgaMmuInfo(struct rga_req *msg,
            		unsigned char  mmu_en,   unsigned char  src_flush,
            		unsigned char  dst_flush,unsigned char  cmd_flush,
            		unsigned int base_addr,  unsigned char  page_size);
#endif

int         NormalRgaMmuFlag(struct rga_req *msg,
                                    int  src_mmu_en,   int  dst_mmu_en);

#endif
