import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

class TDLTextField extends StatefulWidget {
  final TextEditingController controller;

  final String hintText;

  /// true: 右则有个眼睛的按钮，且输入的文字被隐藏了
  final bool obscure;

  final bool isSystem;

  final TextInputType? inputType;

  final Function(String)? onChange;

  final VoidCallback? onEditingComplete;

  final List<TextInputFormatter>? inputFormatters;

  final TextInputAction inputAction;

  final InputBorder? border;

  final Color? primaryColor;
  final Color? textColor;

  final Color? hintColor;
  final Color? fillColor;
  final TextAlign textAlign;
  final bool filled;

  final int? maxLenght;

  final double fontSize;

  final double isSystemVerticalPadding;
  final double verticalPadding;
  final double leftPadding;
  final double rightPadding;
  final double? bottomPadding;
  final Widget? actionIcon;
  final EdgeInsetsGeometry? contentPadding;

  /// [默认是可用的就是true  如果要禁用传false进来]
  final bool enable;

  const TDLTextField(
      {Key? key,
      required this.controller,
      this.hintText = "",
      this.obscure = false,
      this.isSystem = false,
      this.inputType,
      this.onChange,
      this.maxLenght,
      this.onEditingComplete,
      this.inputFormatters,
      this.inputAction = TextInputAction.done,
      this.enable = true,
      this.border,
      this.primaryColor,
      this.hintColor,
      this.textColor,
      this.fontSize = 14,
      this.verticalPadding = 15,
      this.isSystemVerticalPadding = 5,
      this.leftPadding = 15,
      this.rightPadding = 15,
      this.bottomPadding,
      this.filled = true,
      this.fillColor,
      this.actionIcon,
      this.textAlign = TextAlign.start,
      this.contentPadding})
      : super(key: key);
  @override
  FXTextFieldState createState() => FXTextFieldState();
}

class FXTextFieldState extends State<TDLTextField> {
  bool _showPsw = false;
  @override
  Widget build(BuildContext context) {
    if (widget.isSystem) {
      return TextField(
        maxLength: widget.maxLenght,
        controller: widget.controller,
        obscureText: widget.obscure ? !_showPsw : false,
        keyboardType: widget.inputType ?? TextInputType.text,
        onEditingComplete: () {
          FocusScope.of(context).requestFocus(FocusNode());
          widget.onEditingComplete?.call();
        },
        textAlign: widget.textAlign,
        onChanged: (value) {
          widget.onChange?.call(value);
        },
        style: TextStyle(
            color: widget.textColor ?? const Color(0xff212121),
            fontSize: widget.fontSize),
        inputFormatters: widget.inputFormatters ?? <TextInputFormatter>[],
        textInputAction: widget.inputAction,
        
        decoration: InputDecoration(
          isCollapsed: true,
          contentPadding: widget.contentPadding ??
              EdgeInsets.symmetric(vertical: widget.isSystemVerticalPadding),
          // EdgeInsets.only(top: 8),
          border: InputBorder.none,
          hintText: widget.hintText,
          suffixIconConstraints:
              const BoxConstraints(minHeight: 24, minWidth: 24),
          suffixIcon: widget.obscure ? suffixicon : widget.actionIcon,
          floatingLabelAlignment: FloatingLabelAlignment.center,
          hintStyle: TextStyle(fontSize: 14, color: widget.hintColor),
        ),
      );
    }
    return Container(
      // margin: const EdgeInsets.symmetric(vertical: 5),
      padding: const EdgeInsets.symmetric(horizontal: 0),
      child: Theme(
        data: ThemeData(
          hintColor: widget.hintColor ?? const Color(0xff999999),
        ),
        child: TextField(
          maxLength: widget.maxLenght,
          controller: widget.controller,
          obscureText: widget.obscure ? !_showPsw : false,
          onChanged: (value) {
            widget.onChange?.call(value);
          },
          onEditingComplete: () {
            FocusScope.of(context).requestFocus(FocusNode());
            widget.onEditingComplete?.call();
          },
          inputFormatters: widget.inputFormatters ?? <TextInputFormatter>[],
          enabled: widget.enable,
          style: TextStyle(
            fontSize: 14,
            color: widget.textColor ?? Colors.white,
          ),
          keyboardType: widget.inputType ?? TextInputType.text,
          textInputAction: widget.inputAction,
          decoration: InputDecoration(
            isCollapsed: true,
            suffixIcon: widget.obscure ? suffixicon : widget.actionIcon,
            hintText: widget.hintText,
            hintStyle: TextStyle(
              fontSize: widget.fontSize,
            ),
            // fillColor: widget.fillColor ?? const Color.fromRGBO(255, 255, 255, 0.2),
            filled: widget.filled,
            contentPadding: EdgeInsets.only(
              right: widget.rightPadding,
              left: widget.leftPadding,
              top: widget.verticalPadding,
              bottom: widget.bottomPadding ?? widget.verticalPadding,
            ),
            border: widget.border ?? InputBorder.none,
          ),
        ),
      ),
    );
  }

  UnderlineInputBorder get outlineInputBorder => const UnderlineInputBorder(
      borderRadius: BorderRadius.all(Radius.circular(30.0)),
      borderSide: BorderSide(color: Colors.orange));

  Widget get suffixicon => InkWell(
        child: Icon(
          _showPsw ? Icons.lock_open : Icons.lock_outline,
          color: const Color(0xff999999),
          size: 24,
        ),
        onTap: () {
          setState(() {
            _showPsw = !_showPsw;
          });
        },
      );
}

class SystemTextField extends StatefulWidget {
  final bool obscure;
  final TextEditingController controller;
  final String hintText;
  final TextStyle? hintStyle;
  final TextStyle? style;
  final TextInputType? inputType;
  const SystemTextField(
      {Key? key,
      required this.controller,
      this.hintText = "请输入",
      this.inputType,
      this.style,
      this.hintStyle,
      this.obscure = false})
      : super(key: key);
  @override
  SystemTextFieldState createState() => SystemTextFieldState();
}

class SystemTextFieldState extends State<SystemTextField> {
  bool _showPsw = false;

  @override
  Widget build(BuildContext context) {
    return Column(
      children: [
        Row(
          crossAxisAlignment: CrossAxisAlignment.center,
          children: [
            Expanded(
                flex: 1,
                child: TextField(
                  controller: widget.controller,
                  keyboardType: widget.inputType ?? TextInputType.text,
                  style: widget.style ?? const TextStyle(color: Colors.white),
                  obscureText: widget.obscure ? !_showPsw : false,
                  decoration: InputDecoration(
                    hintText: widget.hintText,
                    border: InputBorder.none,
                    hintStyle: widget.hintStyle ??
                        const TextStyle(color: Color(0xff999999)),
                    suffixIcon: widget.obscure ? suffixicon : null,
                    contentPadding:
                        const EdgeInsets.symmetric(horizontal: 16, vertical: 16)
                            .copyWith(bottom: 0),
                  ),
                )),
          ],
        ),
        const Divider(
          height: 0.5,
          color: Colors.white,
        )
      ],
    );
  }

  Widget get suffixicon => IconButton(
        icon: Icon(
          _showPsw ? Icons.remove_red_eye_outlined : Icons.remove_red_eye_sharp,
          color: Colors.white,
          size: 16,
        ),
        onPressed: () {
          setState(() {
            _showPsw = !_showPsw;
          });
        },
      );
}
