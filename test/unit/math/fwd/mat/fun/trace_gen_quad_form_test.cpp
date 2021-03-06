#include <stan/math/fwd/mat.hpp>
#include <gtest/gtest.h>

using stan::math::fvar;

TEST(AgradFwdMatrixTraceGenQuadForm, mat_fd) {
  using stan::math::trace_gen_quad_form;
  using stan::math::matrix_fd;
  
  matrix_fd ad(4,4);
  matrix_fd bd(4,2);
  matrix_fd cd(2,2);
  fvar<double> res;
  
  
  bd << 100, 10,
  0,  1,
  -3, -3,
  5,  2;
  ad << 2.0,  3.0, 4.0,   5.0, 
  6.0, 10.0, 2.0,   2.0,
  7.0,  2.0, 7.0,   1.0,
  8.0,  2.0, 1.0, 112.0;
  cd.setIdentity(2,2);
  
  ad(0,0).d_ = 1.0;
  ad(0,1).d_ = 1.0;
  ad(0,2).d_ = 1.0;
  ad(0,3).d_ = 1.0;
  ad(1,0).d_ = 1.0;
  ad(1,1).d_ = 1.0;
  ad(1,2).d_ = 1.0;
  ad(1,3).d_ = 1.0;
  ad(2,0).d_ = 1.0;
  ad(2,1).d_ = 1.0;
  ad(2,2).d_ = 1.0;
  ad(2,3).d_ = 1.0;
  ad(3,0).d_ = 1.0;
  ad(3,1).d_ = 1.0;
  ad(3,2).d_ = 1.0;
  ad(3,3).d_ = 1.0;
  bd(0,0).d_ = 1.0;
  bd(0,1).d_ = 1.0;
  bd(1,0).d_ = 1.0;
  bd(1,1).d_ = 1.0;
  bd(2,0).d_ = 1.0;
  bd(2,1).d_ = 1.0;
  bd(3,0).d_ = 1.0;
  bd(3,1).d_ = 1.0;
  cd(0,0).d_ = 1.0;
  cd(0,1).d_ = 1.0;
  cd(1,0).d_ = 1.0;
  cd(1,1).d_ = 1.0;

  // fvar<double> - fvar<double> - fvar<double>
  res = trace_gen_quad_form(cd,ad,bd);
  EXPECT_FLOAT_EQ(26758, res.val_);
  EXPECT_FLOAT_EQ(49736, res.d_);
}

TEST(AgradFwdMatrixTraceGenQuadForm, mat_ffd) {
  using stan::math::trace_gen_quad_form;
  using stan::math::matrix_ffd;
  
  matrix_ffd ad(4,4);
  matrix_ffd bd(4,2);
  matrix_ffd cd(2,2);
  fvar<fvar<double> > res;
  
  
  bd << 100, 10,
  0,  1,
  -3, -3,
  5,  2;
  ad << 2.0,  3.0, 4.0,   5.0, 
  6.0, 10.0, 2.0,   2.0,
  7.0,  2.0, 7.0,   1.0,
  8.0,  2.0, 1.0, 112.0;
  cd.setIdentity(2,2);
  
  ad(0,0).d_ = 1.0;
  ad(0,1).d_ = 1.0;
  ad(0,2).d_ = 1.0;
  ad(0,3).d_ = 1.0;
  ad(1,0).d_ = 1.0;
  ad(1,1).d_ = 1.0;
  ad(1,2).d_ = 1.0;
  ad(1,3).d_ = 1.0;
  ad(2,0).d_ = 1.0;
  ad(2,1).d_ = 1.0;
  ad(2,2).d_ = 1.0;
  ad(2,3).d_ = 1.0;
  ad(3,0).d_ = 1.0;
  ad(3,1).d_ = 1.0;
  ad(3,2).d_ = 1.0;
  ad(3,3).d_ = 1.0;
  bd(0,0).d_ = 1.0;
  bd(0,1).d_ = 1.0;
  bd(1,0).d_ = 1.0;
  bd(1,1).d_ = 1.0;
  bd(2,0).d_ = 1.0;
  bd(2,1).d_ = 1.0;
  bd(3,0).d_ = 1.0;
  bd(3,1).d_ = 1.0;
  cd(0,0).d_ = 1.0;
  cd(0,1).d_ = 1.0;
  cd(1,0).d_ = 1.0;
  cd(1,1).d_ = 1.0;

  // fvar<fvar<double> > - fvar<fvar<double> > - fvar<fvar<double> >
  res = trace_gen_quad_form(cd,ad,bd);
  EXPECT_FLOAT_EQ(26758, res.val_.val_);
  EXPECT_FLOAT_EQ(49736, res.d_.val_);
}
