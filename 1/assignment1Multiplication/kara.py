def kara(x,y):
  if (x < 10 or y < 10):
    return x*y
  else:
    x_ = str(x)
    y_ = str(y)
    a_ = x_[:len(x_)//2]
    b_ = x_[len(x_)//2:]
    
    # Ensure that d_ is the same length as b_
    c_ = y_[:-len(b_)]
    d_ = y_[-len(b_):]
    #print(a_,b_,c_,d_)
    a = int(a_)
    b = int(b_)
    c = int(c_)
    d = int(d_)
    ac = kara(a,c)
    ad = kara(a,d)
    bc = kara(b,c)
    bd = kara(b,d)
    #print('ac:', ac, 'ad+bc:', ad+bc, 'bd:', bd)
    return ac*10**(2*len(b_)) + (ad+bc)*10**(len(b_)) + bd
