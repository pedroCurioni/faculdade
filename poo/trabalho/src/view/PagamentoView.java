package view;

import controllers.HospedagemController;
import controllers.MainController;
import dto.PagamentoDto;
import enums.ETipoPagamento;
import exception.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Date;

public class PagamentoView extends JFrame {

    private static final long serialVersionUID = 4576807563416034389L;
    private final HospedagemController hospedagemController = MainController.getHospedagemController();

    private JTextField txtHospedagemId;
    private JComboBox<ETipoPagamento> comboTipoPagamento;
    private JTextField txtValor;

    public PagamentoView() {
        setTitle("Pagamento");
        setSize(600, 400);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        JTabbedPane tabbedPane = new JTabbedPane();
        tabbedPane.addTab("Adicionar Pagamento", createAddPanel());

        add(tabbedPane);
    }

    private JPanel createAddPanel() {
        JPanel addPanel = new JPanel(new GridLayout(4, 2, 10, 10));
        addPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        addPanel.add(new JLabel("ID Hospedagem:"));
        txtHospedagemId = new JTextField();
        addPanel.add(txtHospedagemId);

        addPanel.add(new JLabel("Tipo Pagamento:"));
        comboTipoPagamento = new JComboBox<>(ETipoPagamento.values());
        addPanel.add(comboTipoPagamento);

        addPanel.add(new JLabel("Valor (numérico):"));
        txtValor = new JTextField();
        addPanel.add(txtValor);

        JButton btnAddPagamento = new JButton("Adicionar Pagamento");
        addPanel.add(btnAddPagamento);

        btnAddPagamento.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                addPagamento();
            }
        });

        return addPanel;
    }

    private void addPagamento() {
        try {
            String idHospedagem = txtHospedagemId.getText().trim();
            ETipoPagamento tipoPagamento = (ETipoPagamento) comboTipoPagamento.getSelectedItem();
            double valor = Double.parseDouble(txtValor.getText().trim());
            PagamentoDto pagamentoDto = new PagamentoDto(tipoPagamento, new Date(), valor);
            hospedagemController.addPagamento(idHospedagem, pagamentoDto);
            JOptionPane.showMessageDialog(null, "Pagamento adicionado com sucesso!");
        } catch (HospedagemException | PagamentoException | TipoAcomodacaoException ex) {
            JOptionPane.showMessageDialog(null, ex.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(null, "Formato invalido, campos de número deve conter apenas números", "Erro", JOptionPane.ERROR_MESSAGE);
        } catch (NullPointerException ex) {
            JOptionPane.showMessageDialog(null, "Todos os campos devem ser preenchidos", "Erro", JOptionPane.ERROR_MESSAGE);
        }
    }
}