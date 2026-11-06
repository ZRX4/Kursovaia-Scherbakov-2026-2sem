class ShallowDemo
{
    StringBuilder nickname;
    ShallowDemo(String nick) {this.nickname=new StringBuilder(nick);}
    ShallowDemo (ShallowDemo other){this.nickname=other.nickname;}
    
}