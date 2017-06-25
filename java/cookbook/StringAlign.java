package C03;

import java.text.FieldPosition;
import java.text.Format;
import java.text.ParsePosition;

/**
 * Time: 25/06/17 22:37
 * Created by yaning.
 * School: HUST
 * Email: wangyaning6166@gmail.com
 */
public class StringAlign extends Format {
    private static final long serialVersionUID = 1L;

    public enum Justify {
        /* 左对齐 */
        LEFT,
        /* 居中 */
        CENTER,
        /* 右对齐 */
        RIGHT,
    }

    private Justify justify;
    private int maxChars;

    /**
     * @Description: 构造了一个格式化器
     * @author: Yaning Wang
     * @Param: maxChars 最大长度
     */

    public StringAlign(int maxChars, Justify justify) {
        switch (justify) {
            case LEFT:
            case CENTER:
            case RIGHT:
                this.justify = justify;
                break;
            default:
                throw new IllegalArgumentException("Invalid justification arg.");
        }
        if (maxChars < 0) {
            throw new IllegalArgumentException("maxChars must be positive.");
        }
        this.maxChars = maxChars;
    }


    @Override
    public StringBuffer format(Object input, StringBuffer where, FieldPosition ignore) {
        String s = input.toString();
        String wanted = s.substring(0, Math.min(s.length(), maxChars));
        // 得到右侧的空格
        switch (justify) {
            case RIGHT:
                pad(where, maxChars - wanted.length());
                where.append(wanted);
                break;
            case CENTER:
                int toAdd = maxChars - wanted.length();
                pad(where, toAdd / 2);
                where.append(wanted);
                pad(where, toAdd - toAdd / 2);
                break;
            case LEFT:
                where.append(wanted);
                pad(where, maxChars - wanted.length());
                break;
            default:
                throw new IllegalArgumentException("Argument exception");
        }
        return where;
    }

    protected final void pad(StringBuffer to, int howMany) {
        for (int i = 0; i < howMany; i++) {
            to.append(" ");
        }
    }

    String format(String s) {
        return format(s, new StringBuffer(), null).toString();
    }

    @Override
    public Object parseObject(String source, ParsePosition pos) {
        return source;
    }
}

